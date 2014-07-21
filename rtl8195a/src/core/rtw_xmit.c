/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *                                        
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#define _RTW_XMIT_C_
#include "../include/basic_types.h"
#include "../include/drv_types.h"
#include "../include/rtw_debug.h"
#include "../include/8195_desc.h"
#include "../include/8195_sdio_reg.h"
#include "../include/xmit_osdep.h"
#include "../include/osdep_service.h"
#include "../include/osdep_service_linux.h"
#include "../include/rtw_xmit.h"
static s32 update_txdesc(_adapter *padapter, _pkt *pkt, TXDESC_8195A *ptxdesc)
{
	sint res = _SUCCESS;
	struct pkt_file pktfile;
	struct ethhdr etherhdr;
_func_enter_;
	_rtw_open_pktfile(pkt, &pktfile);
	ptxdesc->txpktsize = pktfile.pkt_len;
_func_exit_;
	return res;	
}
static void TxDescGen(PTXDESC_8195A ptxdesc, u16 pktsize, u16 seqNum)
{
	
//DWORD 0
	ptxdesc->txpktsize = pktsize;
	
	ptxdesc->offset = 0x20;
	
	ptxdesc->bmc = 1;
	ptxdesc->htc = 0;
	ptxdesc->ls = 1;
	ptxdesc->fs = 1;
	ptxdesc->linip = 0;
	ptxdesc->noacm = 0;
	ptxdesc->gf = 0;
	ptxdesc->own = 1;
	
//DWORD 1
	ptxdesc->macid = 0;
	ptxdesc->agg_en = 0;
	ptxdesc->bk = 0;
	ptxdesc->rdg_en = 0;
	
	ptxdesc->qsel = 6;
	ptxdesc->rdg_nav_ext = 0;
	ptxdesc->lsig_txop_en = 0;
	ptxdesc->pifs = 0;
	
	ptxdesc->rate_id = 0;
	ptxdesc->navusehdr = 0;
	ptxdesc->en_desc_id = 1;
	ptxdesc->sectype = 0;
	
	ptxdesc->rsvd2 = 0;
	ptxdesc->pkt_offset = 0;
	ptxdesc->rsvd3 = 0;
	
//DWORD 2
	ptxdesc->rts_rc = 0;
	ptxdesc->data_rc = 0;
	ptxdesc->rsvd8 = 0;
	ptxdesc->bar_rty_th = 0;
	
	ptxdesc->rsvd4 = 0;
	ptxdesc->morefrag = 0;
	ptxdesc->raw = 0;
	ptxdesc->ccx = 0;
	ptxdesc->ampdu_density = 7;
	ptxdesc->rsvd5 = 0;
	
	ptxdesc->antsel_a = 0;
	ptxdesc->antsel_b =0;
	ptxdesc->tx_ant_cck = 0;
	ptxdesc->tx_antl = 0;
	ptxdesc->tx_antht = 0;
	
//DWORD 3
	ptxdesc->nextheadpage = 0;
	ptxdesc->tailpage = 0;
	ptxdesc->seq = seqNum;
	ptxdesc->pkt_id = 0;
	
//DWORD 4
	ptxdesc->rtsrate = 3;
	ptxdesc->ap_dcfe = 0;
	ptxdesc->qos =1;
	ptxdesc->hwseq_en =0;
	
	ptxdesc->userate = 1;
	ptxdesc->disrtsfb =1;
	ptxdesc->disdatafb =1;
	ptxdesc->cts2self =0;
	ptxdesc->rtsen =0;
	ptxdesc->hw_rts_en = 0;
	ptxdesc->port_toggle =0;
	ptxdesc->rsvd6 =0;
	
	ptxdesc->rsvd7 =0;
	ptxdesc->wait_dcts =0;
	ptxdesc->cts2ap_en=0;
	ptxdesc->data_txsc=0;
	
	ptxdesc->data_short =0;
	ptxdesc->databw =0;
	ptxdesc->rts_short =0;
	ptxdesc->rtsbw =0;
	ptxdesc->rts_sc =0;
	ptxdesc->vcs_stbc=0;
	
//DWORD 5
	ptxdesc->datarate = 0;
	
	ptxdesc->data_ratefb_lmt =0;
	ptxdesc->rts_ratefb_lmt =0;
	ptxdesc->rty_en =0;
	ptxdesc->data_rt_lmt =0;
	
	ptxdesc->usb_txagg_num=0;
	
//DWORD 6
	ptxdesc->txagc_a = 0;
	ptxdesc->txagc_b =0;
	ptxdesc->use_max_len =0;
	ptxdesc->max_agg_num = 0xf;
	
	ptxdesc->mcsg1_max_len = 8;
	ptxdesc->mcsg2_max_len =8;
	
	ptxdesc->mcsg3_max_len = 8;
	ptxdesc->mcsg7_max_len =8;
	
//DWORD 7
	ptxdesc->txbuffsize = 0x7da0;
	
	ptxdesc->mcsg4_max_len =0;
	ptxdesc->mcsg5_max_len =0;
	ptxdesc->mcsg6_max_len =0;
	ptxdesc->mcsg15_max_len =0;
	
}

/*
 * The main transmit(tx) entry
 *
 * Return
 *	1	enqueue
 *	0	success, hardware will handle this xmit frame(packet)
 *	<0	fail
 */
 
s32 rtw_xmit(_adapter *padapter, _pkt **ppkt)
{
	static u32 start = 0;
	static u32 drop_cnt = 0;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	struct xmit_frame *pxmitframe = NULL;
	TXDESC_8195A txdesc;
	struct xmit_buf *pxmitbuf;
	s32 res;
	struct intf_hdl *pintfhdl;
	_pkt *skb;
	struct pkt_file pfile;
	DBG_871X("%s(): ==> xmit wanted!\n", __FUNCTION__);

//		pfile.pkt = *ppkt;
//		pfile.cur_addr = pfile.buf_start = *ppkt->data;
//		pfile.pkt_len = pfile.buf_len = *skb->len;
//		skb =  *ppkt;
//		pintfhdl->padapter = padapter;
//		pxmitbuf = (struct xmit_buf *)rtw_zmalloc(sizeof(*pxmitbuf));
//		_rtw_memcpy(pxmitbuf->pdata, skb->data, skb->len);
//			_rtw_init_listhead(&pxmitbuf->list);
//	
//			pxmitbuf->priv_data = NULL;
//			pxmitbuf->padapter = padapter;
//			pxmitbuf->buf_tag = XMITBUF_DATA;
//			pxmitbuf->pallocated_buf = rtw_zmalloc(MAX_XMITBUF_SZ + XMITBUF_ALIGN_SZ);
//			if (pxmitbuf->pallocated_buf == NULL)
//			{
//				return _FAIL;
//			}
//	
//			pxmitbuf->pbuf = (u8 *)N_BYTE_ALIGMENT((SIZE_PTR)(pxmitbuf->pallocated_buf), XMITBUF_ALIGN_SZ);
//	#if defined(CONFIG_SDIO_HCI) || defined(CONFIG_GSPI_HCI)
//			pxmitbuf->phead = pxmitbuf->pbuf;
//			pxmitbuf->pend = pxmitbuf->pbuf + MAX_XMITBUF_SZ;
//			pxmitbuf->len = 0;
//			pxmitbuf->pdata = pxmitbuf->ptail = pxmitbuf->phead;
//	#endif
//	
//			pxmitbuf->flags = XMIT_VO_QUEUE;
//		if (start == 0)
//			start = rtw_get_current_time();

//	pxmitframe = rtw_alloc_xmitframe(pxmitpriv);

//		if (rtw_get_passing_time_ms(start) > 2000) {
//			if (drop_cnt)
//				DBG_871X("DBG_TX_DROP_FRAME %s no more pxmitframe, drop_cnt:%u\n", __FUNCTION__, drop_cnt);
//			start = rtw_get_current_time();
//			drop_cnt = 0;
//		}
//	
//		if (pxmitframe == NULL) {
//			drop_cnt ++;
//			RT_TRACE(_module_xmit_osdep_c_, _drv_err_, ("rtw_xmit: no more pxmitframe\n"));
//			return -1;
//		}

//		res = update_txdesc(padapter, *ppkt, &txdesc);
//		TxDescGen(&txdesc, txdesc.txpktsize, 1);
//		pxmitframe->pxmitbuf = pxmitbuf;
//		pxmitframe->pkt = *ppkt;
//	
//		skb = *ppkt;	
//		_rtw_memcpy(pxmitbuf->pdata, skb->data, skb->len);
//	sdio_write_port(pintfhdl, WLAN_TX_HIQ_DEVICE_ID, txdesc.txpktsize, pxmitbuf);
//		if (rtw_hal_xmit(padapter, pxmitframe) == _FALSE)
//			return 1;

	return 0;
}

