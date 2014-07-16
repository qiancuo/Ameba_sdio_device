#include "../../include/osdep_service_linux.h"

//	u8* _rtw_malloc(u32 sz)
//	{
//		u8 *pbuf=NULL;
//		pbuf = kmalloc(sz, in_interrupt()?GFP_ATOMIC : GFP_KERNEL);
//	
//		return pbuf;
//	}
//	
//	void _rtw_mfree(u8 *pbuf, u32 sz)
//	{
//		kfree(pbuf);
//	}
//	
//	void _rtw_memcpy(void* dst, void* src, u32 sz)
//	{
//		memcpy(dst, src, sz);
//	}

void DumpForOneBytes(IN u8 *pData, IN u8 Len)
{
	u8 *pSbuf = pData;	
	s8 Length=Len;

	s8 LineIndex=0,BytesIndex,Offset;
	printk("\r [Addr]   .0 .1 .2 .3 .4 .5 .6 .7 .8 .9 .A .B .C .D .E .F\r\n" );

	while( LineIndex< Length)
	{		
			printk("%08x: ", (pSbuf+LineIndex) );

			if(LineIndex+16 < Length)
				Offset=16;
			else			
				Offset=Length-LineIndex;
			

			for(BytesIndex=0; BytesIndex<Offset; BytesIndex++)
				printk("%02x ", pSbuf[LineIndex+BytesIndex]);	

			for(BytesIndex=0;BytesIndex<16-Offset;BytesIndex++)	//a last line
    			printk("   ");


			printk("    ");		//between byte and char
			
			for(BytesIndex=0;  BytesIndex<Offset; BytesIndex++) {
                
				if( ' ' <= pSbuf[LineIndex+BytesIndex]  && pSbuf[LineIndex+BytesIndex] <= '~')
					printk("%c", pSbuf[LineIndex+BytesIndex]);
				else
					printk(".");
			}
            
			printk("\n\r");
			LineIndex += 16;
	}
	
}