#include "sdio/8195_desc.h"
#include "sdio/8195_sdio_reg.h"
#include "8195_common.h"
#include "sdio/sdio_io.h"
#include "dispatchreadwrite.h"


static unsigned long get_deviceid(ULONG addr)
{
	


	switch( (addr & 0xffff0000) )
	{
	case SDIO_LOCAL_OFFSET:

		return SDIO_LOCAL_DEVICE_ID;

	case WLAN_IOREG_OFFSET:

		return WLAN_IOREG_DEVICE_ID;

	case TX_LOQ_OFFSET:
		return WLAN_LOQ_DEVICE_ID;
		
       case TX_MIQ_OFFSET:
	   	return WLAN_MIQ_DEVICE_ID;
		
       case TX_HIQ_OFFSET:
	   	return WLAN_HIQ_DEVICE_ID;
		
	case RX_RXOFF_OFFSET:
		return WLAN_RX0FF_DEVICE_ID;
	
//	case WLAN_FIFO_OFFSET:
//		return WLAN_FIFO_DEVICE_ID;
	default:
	#if 0	
		if(((addr & 0xfff00000) == RTL8712_IOBASE_FF) && ((addr & 0x000fffff)< 0xaffff))
		{

			return DID_WLAN_FIFO;
		}
		else
		{
//			RT_TRACE(_module_hci_ops_c_,_drv_err_,(" error:  something wrong in get_deviceid \n"));
		}
		break;
	#endif
		return UNDEFINED_DEVICE_ID;	//Undefine Address. Register R/W Protocol is needed.
	}


	
	
	
	
}




ULONG  _cvrt2ftaddr(const ULONG addr, ULONG *pftaddr)  
{
	


	switch(get_deviceid(addr))
	{
			
		case SDIO_LOCAL_DEVICE_ID:
			//KdPrint(("\nSDIO_LOCAL_ADDR: %x\n",addr));	
			*pftaddr = ((SDIO_LOCAL_DEVICE_ID << 13) | (addr & SDIO_LOCAL_MSK));
			return SUCCESS;
			
		case WLAN_IOREG_DEVICE_ID:
			//KdPrint(("WLAN_IOREG_ADDR: %x\n",addr));	
			*pftaddr = ((WLAN_IOREG_DEVICE_ID << 13) | (addr & WLAN_IOREG_MSK));
			return SUCCESS; //using cmd52 to access
			
		case WLAN_HIQ_DEVICE_ID:
			*pftaddr = ((WLAN_HIQ_DEVICE_ID << 13) | (addr & WLAN_FIFO_MSK));
			return SUCCESS;
		case WLAN_MIQ_DEVICE_ID:
			*pftaddr = ((WLAN_MIQ_DEVICE_ID << 13) | (addr & WLAN_FIFO_MSK));
			return SUCCESS;
		case WLAN_LOQ_DEVICE_ID:
			*pftaddr = ((WLAN_LOQ_DEVICE_ID << 13) | (addr & WLAN_FIFO_MSK));
			return SUCCESS;
		case WLAN_RX0FF_DEVICE_ID:
			*pftaddr = ((WLAN_RX0FF_DEVICE_ID << 13) | (addr & WLAN_FIFO_MSK));
			return SUCCESS;	

		default:
		
			printk(("\nFAIL To Translate Address: %x\n",addr));	
			return FAIL;
	}
}



static ULONG TransferPriorityQueueAddr(UCHAR QueueToPriority)
{

	ULONG addr = 0 ;

	switch(QueueToPriority)
	{
		case LOW_QUEUE:
			addr = TX_LOQ_OFFSET;
			break;
		case NORMAL_QUEUE:
			addr = TX_MIQ_OFFSET;
			break;
		case HI_QUEUE:
			addr = TX_HIQ_OFFSET;
			break;
		default:
			addr = 0 ;

	}
	return addr;

}
#define AGG_LEN_UNIT 4
u32 getqueueaddr(u8 *pBuf, u32 length, BOOLEAN bIsWrite)
{
//	u8 *data = NULL;
	u32 ret;
	u32 q_addr = 0, fourbyte_addr =0;
//	PTX_QUEUE_MAPPING pTxQMapping = NULL;
//	PTX_DESC pdesc = NULL;
//	pTxQMapping->VOQueueToPriorty = HI_QUEUE;//value is 3, just for test, need to confirm<Chris>

	fourbyte_addr=length/AGG_LEN_UNIT+((length%AGG_LEN_UNIT)?1:0);  //mapping Tx aggregation length into unit of 4 byte
	fourbyte_addr &= 0x1fff; //Get Aggregation length //KaiYuan modified for 88e
	q_addr = 0x10310000;
#if 0
	data = pBuf;
	if(bIsWrite)
	{
		pdesc = (PTX_DESC)(data);
		switch(pdesc->qsel)
		{
			case VO_Q:
				q_addr =  TransferPriorityQueueAddr(pTxQMapping->VOQueueToPriorty);
				break;
			case VI_Q:
				q_addr =  TransferPriorityQueueAddr(pTxQMapping->VIQueueToPriorty);
				break;
			case BE_Q:
				q_addr =  TransferPriorityQueueAddr(pTxQMapping->BEQueueToPriorty);
				break;
			case BK_Q:
				q_addr =  TransferPriorityQueueAddr(pTxQMapping->BKQueueToPriorty);
				break;
			case BCN_Q:
				q_addr =  TransferPriorityQueueAddr(pTxQMapping->HIQueueToPriorty);
				break;
			case CMD_Q:
				q_addr =  TransferPriorityQueueAddr(pTxQMapping->MGQueueToPriorty);
				break;
			default:
//				KdPrint(("Invalid queue :%d\n",pdesc->qsel));
				q_addr = 0 ;
					
		}
#endif

		if(q_addr)//Include Aggregation length 
		{
			q_addr |= fourbyte_addr;
		}
//	}
#if 0
	else // For RX FIFO //Not used
	{
		//Set RX FIFO address and seq number	
		q_addr = WLAN_FIFO_RX ;
		//increase_rx_seq_num(prx_priv, &q_addr);
	}
#endif

	return q_addr;
}

int dispatchreadwrite(IN struct sdio_func * func, u8 *pData, u32 totalLength, BOOLEAN bIsWrite)
{
	u32 queue_address =0;
	int ret;
	u32 fourbyte_len = 0;
	u8 *pBuf;
	pBuf = pData;
	printk("totallength is %d \n", totalLength);
	queue_address = getqueueaddr(pBuf, totalLength, bIsWrite);
	printk("queue_address is 0x%x \n", queue_address);
	if(!queue_address)
	{
		return -1;
	}

   	fourbyte_len=AGG_LEN_UNIT*(totalLength/AGG_LEN_UNIT+((totalLength%AGG_LEN_UNIT)?1:0));  //mapping Tx aggregation length into unit of 4 byte

	if(12==(fourbyte_len%512))
	{
		fourbyte_len+=4;
	}

	printk("fourbyte_len is %d \n", fourbyte_len);

	ret = sdioReadWrite_CMD53_byte(func, pBuf, queue_address, fourbyte_len, bIsWrite);

	return ret;
	
}
