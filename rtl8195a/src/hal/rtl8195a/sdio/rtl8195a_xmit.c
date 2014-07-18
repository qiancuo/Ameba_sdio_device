#define __RTL8195A_XMIT_C__
//	void TxDescGen(PTXDESC_8195A ptxdesc, u16 pktsize, u16 seqNum)
//	{
//	
//	//DWORD 0
//		ptxdesc->txpktsize = pktsize;
//	
//		ptxdesc->offset = 0x20;
//	
//		ptxdesc->bmc = 1;
//		ptxdesc->htc = 0;
//		ptxdesc->ls = 1;
//		ptxdesc->fs = 1;
//		ptxdesc->linip = 0;
//		ptxdesc->noacm = 0;
//		ptxdesc->gf = 0;
//		ptxdesc->own = 1;
//	
//	//DWORD 1
//		ptxdesc->macid = 0;
//		ptxdesc->agg_en = 0;
//		ptxdesc->bk = 0;
//		ptxdesc->rdg_en = 0;
//	
//		ptxdesc->qsel = 6;
//		ptxdesc->rdg_nav_ext = 0;
//		ptxdesc->lsig_txop_en = 0;
//		ptxdesc->pifs = 0;
//	
//		ptxdesc->rate_id = 0;
//		ptxdesc->navusehdr = 0;
//		ptxdesc->en_desc_id = 1;
//		ptxdesc->sectype = 0;
//	
//		ptxdesc->rsvd2 = 0;
//		ptxdesc->pkt_offset = 0;
//		ptxdesc->rsvd3 = 0;
//	
//	//DWORD 2
//		ptxdesc->rts_rc = 0;
//		ptxdesc->data_rc = 0;
//		ptxdesc->rsvd8 = 0;
//		ptxdesc->bar_rty_th = 0;
//	
//		ptxdesc->rsvd4 = 0;
//		ptxdesc->morefrag = 0;
//		ptxdesc->raw = 0;
//		ptxdesc->ccx = 0;
//		ptxdesc->ampdu_density = 7;
//		ptxdesc->rsvd5 = 0;
//	
//		ptxdesc->antsel_a = 0;
//		ptxdesc->antsel_b =0;
//		ptxdesc->tx_ant_cck = 0;
//		ptxdesc->tx_antl = 0;
//		ptxdesc->tx_antht = 0;
//	
//	//DWORD 3
//		ptxdesc->nextheadpage = 0;
//		ptxdesc->tailpage = 0;
//		ptxdesc->seq = seqNum;
//		ptxdesc->pkt_id = 0;
//	
//	//DWORD 4
//		ptxdesc->rtsrate = 3;
//		ptxdesc->ap_dcfe = 0;
//		ptxdesc->qos =1;
//		ptxdesc->hwseq_en =0;
//	
//		ptxdesc->userate = 1;
//		ptxdesc->disrtsfb =1;
//		ptxdesc->disdatafb =1;
//		ptxdesc->cts2self =0;
//		ptxdesc->rtsen =0;
//		ptxdesc->hw_rts_en = 0;
//		ptxdesc->port_toggle =0;
//		ptxdesc->rsvd6 =0;
//	
//		ptxdesc->rsvd7 =0;
//		ptxdesc->wait_dcts =0;
//		ptxdesc->cts2ap_en=0;
//		ptxdesc->data_txsc=0;
//	
//		ptxdesc->data_short =0;
//		ptxdesc->databw =0;
//		ptxdesc->rts_short =0;
//		ptxdesc->rtsbw =0;
//		ptxdesc->rts_sc =0;
//		ptxdesc->vcs_stbc=0;
//	
//	//DWORD 5
//		ptxdesc->datarate = 0;
//	
//		ptxdesc->data_ratefb_lmt =0;
//		ptxdesc->rts_ratefb_lmt =0;
//		ptxdesc->rty_en =0;
//		ptxdesc->data_rt_lmt =0;
//	
//		ptxdesc->usb_txagg_num=0;
//	
//	//DWORD 6
//		ptxdesc->txagc_a = 0;
//		ptxdesc->txagc_b =0;
//		ptxdesc->use_max_len =0;
//		ptxdesc->max_agg_num = 0xf;
//	
//		ptxdesc->mcsg1_max_len = 8;
//		ptxdesc->mcsg2_max_len =8;
//	
//		ptxdesc->mcsg3_max_len = 8;
//		ptxdesc->mcsg7_max_len =8;
//	
//	//DWORD 7
//		ptxdesc->txbuffsize = 0x7da0;
//	
//		ptxdesc->mcsg4_max_len =0;
//		ptxdesc->mcsg5_max_len =0;
//		ptxdesc->mcsg6_max_len =0;
//		ptxdesc->mcsg15_max_len =0;
//		
//	}

void rtl8188es_fill_default_txdesc(
	struct xmit_frame *pxmitframe,
	u8 *pbuf)
{
	PADAPTER padapter;
	HAL_DATA_TYPE *pHalData;
	struct mlme_ext_priv *pmlmeext;
	struct mlme_ext_info *pmlmeinfo;
//	struct dm_priv *pdmpriv;
	struct pkt_attrib *pattrib;
	PTXDESC_8195A ptxdesc;
	s32 bmcst;

	ptxdesc = (PTXDESC_8195A)pbuf;
//		padapter = pxmitframe->padapter;
//		pHalData = GET_HAL_DATA(padapter);
//		//pdmpriv = &pHalData->dmpriv;
//		pmlmeext = &padapter->mlmeextpriv;
//		pmlmeinfo = &(pmlmeext->mlmext_info);
//	
//		pattrib = &pxmitframe->attrib;
//		bmcst = IS_MCAST(pattrib->ra);
//	
//		ptxdesc = (PTXDESC_8195A)pbuf;
//	
//	
//		if (pxmitframe->frame_tag == DATA_FRAMETAG)
//		{
//			ptxdesc->macid = pattrib->mac_id; // CAM_ID(MAC_ID)
//	
//			if (pattrib->ampdu_en == _TRUE)
//				ptxdesc->agg_en = 1; // AGG EN
//			else
//				ptxdesc->bk = 1; // AGG BK
//	
//			ptxdesc->qsel = pattrib->qsel;
//			ptxdesc->rate_id = pattrib->raid;
//	
//			fill_txdesc_sectype(pattrib, ptxdesc);
//	
//			ptxdesc->seq = pattrib->seqnum;
//	
//			//todo: qos_en
//	
//			ptxdesc->userate = 1; // driver uses rate	
//	
//			if ((pattrib->ether_type != 0x888e) &&
//				(pattrib->ether_type != 0x0806) &&
//				(pattrib->dhcp_pkt != 1))
//			{
//				// Non EAP & ARP & DHCP type data packet
//	
//				fill_txdesc_vcs(pattrib, ptxdesc);
//				fill_txdesc_phy(pattrib, ptxdesc);
//	
//				ptxdesc->rtsrate = 8; // RTS Rate=24M
//				ptxdesc->data_ratefb_lmt = 0x1F;
//				ptxdesc->rts_ratefb_lmt = 0xF;
//	
//	#if (RATE_ADAPTIVE_SUPPORT == 1)
//				/* driver-based RA*/
//				if (pattrib->ht_en)
//					ptxdesc->sgi = ODM_RA_GetShortGI_8188E(&pHalData->odmpriv,pattrib->mac_id);
//				ptxdesc->datarate = ODM_RA_GetDecisionRate_8188E(&pHalData->odmpriv,pattrib->mac_id);
//	
//				#if (POWER_TRAINING_ACTIVE==1)
//				ptxdesc->pwr_status = ODM_RA_GetHwPwrStatus_8188E(&pHalData->odmpriv,pattrib->mac_id);
//				#endif
//	#else /* (RATE_ADAPTIVE_SUPPORT == 1) */
//				/* FW-based RA, TODO */
//				if(pattrib->ht_en)
//					ptxdesc->sgi = 1;
//	
//				ptxdesc->datarate = 0x13; //MCS7
//	#endif /* (RATE_ADAPTIVE_SUPPORT == 1) */
//	
//				if (padapter->fix_rate != 0xFF) {
//					ptxdesc->userate = 1;
//					ptxdesc->datarate = padapter->fix_rate;
//					ptxdesc->disdatafb = 1;
//					ptxdesc->sgi = (padapter->fix_rate & BIT(7))?1:0;
//				}
//			}
//			else
//			{
//				// EAP data packet and ARP and DHCP packet.
//				// Use the 1M or 6M data rate to send the EAP/ARP packet.
//				// This will maybe make the handshake smooth.
//	
//				ptxdesc->bk = 1; // AGG BK	
//	
//				if (pmlmeinfo->preamble_mode == PREAMBLE_SHORT)
//					ptxdesc->data_short = 1;// DATA_SHORT
//	
//				ptxdesc->datarate = MRateToHwRate(pmlmeext->tx_rate);
//			}
//	
//			ptxdesc->usb_txagg_num = pxmitframe->agg_num;
//		}
//		else if (pxmitframe->frame_tag == MGNT_FRAMETAG)
//		{
//	//		RT_TRACE(_module_hal_xmit_c_, _drv_notice_, ("%s: MGNT_FRAMETAG\n", __FUNCTION__));
//	
//			ptxdesc->macid = pattrib->mac_id; // CAM_ID(MAC_ID)
//			ptxdesc->qsel = pattrib->qsel;
//			ptxdesc->rate_id = pattrib->raid; // Rate ID
//			ptxdesc->seq = pattrib->seqnum;
//			ptxdesc->userate = 1; // driver uses rate, 1M
//			ptxdesc->rty_lmt_en = 1; // retry limit enable
//			ptxdesc->data_rt_lmt = 6; // retry limit = 6
//	
//	#ifdef CONFIG_XMIT_ACK
//			//CCX-TXRPT ack for xmit mgmt frames.
//			if (pxmitframe->ack_report) {
//				#ifdef DBG_CCX
//				static u16 ccx_sw = 0x123;
//				txdesc_set_ccx_sw_88e(ptxdesc, ccx_sw);
//				DBG_871X("%s set ccx, sw:0x%03x\n", __func__, ccx_sw);
//				ccx_sw = (ccx_sw+1)%0xfff;
//				#endif
//				ptxdesc->ccx = 1;
//			}
//	#endif //CONFIG_XMIT_ACK
//	
//	#ifdef CONFIG_INTEL_PROXIM
//			if((padapter->proximity.proxim_on==_TRUE)&&(pattrib->intel_proxim==_TRUE)){
//				DBG_871X("\n %s pattrib->rate=%d\n",__FUNCTION__,pattrib->rate);
//				ptxdesc->datarate = pattrib->rate;
//			}
//			else
//	#endif
//			{
//				ptxdesc->datarate = MRateToHwRate(pmlmeext->tx_rate);
//			}
//		}
//		else if (pxmitframe->frame_tag == TXAGG_FRAMETAG)
//		{
//			RT_TRACE(_module_hal_xmit_c_, _drv_warning_, ("%s: TXAGG_FRAMETAG\n", __FUNCTION__));
//		}
//	#ifdef CONFIG_MP_INCLUDED
//		else if (pxmitframe->frame_tag == MP_FRAMETAG)
//		{
//			struct tx_desc *pdesc;
//	
//			pdesc = (struct tx_desc*)ptxdesc;
//			RT_TRACE(_module_hal_xmit_c_, _drv_notice_, ("%s: MP_FRAMETAG\n", __FUNCTION__));
//			fill_txdesc_for_mp(padapter, (u8 *)pdesc);
//	
//			pdesc->txdw0 = le32_to_cpu(pdesc->txdw0);
//			pdesc->txdw1 = le32_to_cpu(pdesc->txdw1);
//			pdesc->txdw2 = le32_to_cpu(pdesc->txdw2);
//			pdesc->txdw3 = le32_to_cpu(pdesc->txdw3);
//			pdesc->txdw4 = le32_to_cpu(pdesc->txdw4);
//			pdesc->txdw5 = le32_to_cpu(pdesc->txdw5);
//			pdesc->txdw6 = le32_to_cpu(pdesc->txdw6);
//			pdesc->txdw7 = le32_to_cpu(pdesc->txdw7);
//		}
//	#endif // CONFIG_MP_INCLUDED
//		else
//		{
//			RT_TRACE(_module_hal_xmit_c_, _drv_warning_, ("%s: frame_tag=0x%x\n", __FUNCTION__, pxmitframe->frame_tag));
//	
//			ptxdesc->macid = 4; // CAM_ID(MAC_ID)
//			ptxdesc->rate_id = 6; // Rate ID
//			ptxdesc->seq = pattrib->seqnum;
//			ptxdesc->userate = 1; // driver uses rate
//			ptxdesc->datarate = MRateToHwRate(pmlmeext->tx_rate);
//		}
//	
//		ptxdesc->pktlen = pattrib->last_txcmdsz;
//		if (pxmitframe->frame_tag == DATA_FRAMETAG){
//			#ifdef CONFIG_TX_EARLY_MODE
//			ptxdesc->offset = TXDESC_SIZE +EARLY_MODE_INFO_SIZE ;
//			ptxdesc->pkt_offset = 0x01;
//			#else
//			ptxdesc->offset = TXDESC_SIZE ;
//			ptxdesc->pkt_offset = 0;
//			#endif
//		}
//		else{
//			ptxdesc->offset = TXDESC_SIZE ;
//		}
//		
//		if (bmcst) ptxdesc->bmc = 1;
//		ptxdesc->ls = 1;
//		ptxdesc->fs = 1;
//		ptxdesc->own = 1;
//	
//		// 2009.11.05. tynli_test. Suggested by SD4 Filen for FW LPS.
//		// (1) The sequence number of each non-Qos frame / broadcast / multicast /
//		// mgnt frame should be controled by Hw because Fw will also send null data
//		// which we cannot control when Fw LPS enable.
//		// --> default enable non-Qos data sequense number. 2010.06.23. by tynli.
//		// (2) Enable HW SEQ control for beacon packet, because we use Hw beacon.
//		// (3) Use HW Qos SEQ to control the seq num of Ext port non-Qos packets.
//		// 2010.06.23. Added by tynli.
//		if (!pattrib->qos_en)
//		{
//			// Hw set sequence number
//			ptxdesc->hwseq_en = 1; // HWSEQ_EN
//			ptxdesc->hwseq_sel = 0; // HWSEQ_SEL
//		}
//	
}

