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
#define _XMIT_OSDEP_C_

#include "../../include/drv_types.h"
#include "../../include/rtw_debug.h"
#include "../../include/xmit_osdep.h"
#include "../../include/8195_desc.h"
#include "../../include/8195_sdio_reg.h"
#include "../../include/sdio_ops.h"

uint rtw_remainder_len(struct pkt_file *pfile)
{
	return (pfile->buf_len - ((SIZE_PTR)(pfile->cur_addr) - (SIZE_PTR)(pfile->buf_start)));
}

void _rtw_open_pktfile (_pkt *pktptr, struct pkt_file *pfile)
{
_func_enter_;

	pfile->pkt = pktptr;
	pfile->cur_addr = pfile->buf_start = pktptr->data;
	pfile->pkt_len = pfile->buf_len = pktptr->len;

	pfile->cur_buffer = pfile->buf_start ;
	
_func_exit_;
}

uint _rtw_pktfile_read (struct pkt_file *pfile, u8 *rmem, uint rlen)
{	
	uint	len = 0;
	
_func_enter_;

       len =  rtw_remainder_len(pfile);
      	len = (rlen > len)? len: rlen;

       if(rmem)
	  skb_copy_bits(pfile->pkt, pfile->buf_len-pfile->pkt_len, rmem, len);

       pfile->cur_addr += len;
       pfile->pkt_len -= len;
	   
_func_exit_;	       		

	return len;	
}

sint rtw_endofpktfile(struct pkt_file *pfile)
{
_func_enter_;

	if (pfile->pkt_len == 0) {
_func_exit_;
		return _TRUE;
	}

_func_exit_;

	return _FALSE;
}


int _rtw_xmit_entry(_pkt *pkt, _nic_hdl pnetdev)
{
	_adapter *padapter = (_adapter *)rtw_netdev_priv(pnetdev);
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	s32 res = 0;
#if (LINUX_VERSION_CODE>=KERNEL_VERSION(2,6,35))
	u16 queue;
#endif

_func_enter_;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("+xmit_enry\n"));

//		if (rtw_if_up(padapter) == _FALSE) {
//			RT_TRACE(_module_xmit_osdep_c_, _drv_err_, ("rtw_xmit_entry: rtw_if_up fail\n"));
//			#ifdef DBG_TX_DROP_FRAME
//			DBG_871X("DBG_TX_DROP_FRAME %s if_up fail\n", __FUNCTION__);
//			#endif
//			goto drop_packet;
//		}

//	rtw_check_xmit_resource(padapter, pkt);

	res = rtw_xmit(padapter, &pkt);
	if (res < 0) {
		#ifdef DBG_TX_DROP_FRAME
		DBG_871X("DBG_TX_DROP_FRAME %s rtw_xmit fail\n", __FUNCTION__);
		#endif
		goto drop_packet;
	}

	RT_TRACE(_module_xmit_osdep_c_, _drv_info_, ("rtw_xmit_entry: tx_pkts=%d\n", (u32)pxmitpriv->tx_pkts));
	goto exit;

drop_packet:
	pxmitpriv->tx_drop++;
	rtw_skb_free(pkt);
	RT_TRACE(_module_xmit_osdep_c_, _drv_notice_, ("rtw_xmit_entry: drop, tx_drop=%d\n", (u32)pxmitpriv->tx_drop));

exit:

_func_exit_;

	return 0;
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
extern PHAL_DATA_TYPE gHal_Data;
int rtw_xmit_entry(_pkt *pkt, _nic_hdl pnetdev)
{
	int ret = 0;
	struct pkt_file pfile;
	struct intf_hdl *pintfhdl;
	u8 *pxmitbuf;
	TXDESC_8195A txdesc;
	struct sdio_func *pfunc;
	DBG_871X("%s(): ==> xmit wanted!\n", __FUNCTION__);
	CHRIS_ADAPTER *padapter = (CHRIS_ADAPTER *)rtw_netdev_priv(pnetdev);
//	padapter->hw_init_completed = (u8 *)rtw_zmalloc(sizeof(u8));
//	pxmitbuf = (u8 *)rtw_zmalloc(2048);
//		if((padapter->hw_init_completed == NULL))
//		{	
//			DBG_871X("%s(): ==> padapter->hw_init_completed is null\n", __FUNCTION__);
//			return ret;
//		}
//		padapter->hw_init_completed = _TRUE;
//	pintfhdl->padapter = padapter;
//	pintfhdl->pintf_dev = padapter->dvobj;
	if(!gHal_Data->func)
	{
		DBG_871X("%s(): ==> gHal_Data->func is null\n", __FUNCTION__);
		return ret;
	}
	if (pkt) {
//		rtw_mstat_update(MSTAT_TYPE_SKB, MSTAT_ALLOC_SUCCESS, pkt->truesize);
//		ret = _rtw_xmit_entry(pkt, pnetdev);
		pfile.pkt = pkt;
		pfile.cur_addr = pfile.buf_start = pkt->data;
		pfile.pkt_len = pfile.buf_len = pkt->len;
		pfile.cur_buffer = pfile.buf_start;
//		pxmitbuf = pfile.cur_buffer;
		
		txdesc.txpktsize = pfile.pkt_len;
		TxDescGen(&txdesc, txdesc.txpktsize, 1);
		DBG_871X("%s(): ==> skb len is : %d\n", __FUNCTION__, txdesc.txpktsize);		
		pfunc = padapter->func;
		_rtw_memcpy(pxmitbuf, &txdesc, txdesc.offset);
		_rtw_memcpy((pxmitbuf+txdesc.offset), pfile.cur_buffer, txdesc.txpktsize);
		chris_sdio_write_port(pfunc, WLAN_TX_HIQ_DEVICE_ID, (txdesc.txpktsize+txdesc.offset), pxmitbuf);
	}
//	rtw_mfree(padapter->hw_init_completed, sizeof(u8));
//	rtw_mfree(pxmitbuf, sizeof(*pxmitbuf));
	rtw_mfree(pxmitbuf, 2048);
	return ret;
}
