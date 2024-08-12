  extern void enumaration();
 
 
 
 
           char cynt=0,byt,i,lenght=0;
           unsigned char affbuff[100]     absolute 0x00;
           unsigned char bdnbuff[16]     absolute 0x400;
           unsigned char readbuff[0x100]  absolute 0x500;
           unsigned char writebuff[0x100] absolute 0x600;

           
           

    
     void init_sys(){
        cmcon=0x7;  ADCON1=15 ;  TRISB=0xff;   TRISD=0; TRISE=0;
        for(i=0;i<16;i++){bdnbuff[i]=0;}  for(i=0;i<0xff;i++){readbuff[i]=0;writebuff[i]=0;}   readbuff[0xff]=0;writebuff[0xff]=0;
        //porte.b1=0  ;delay_ms(100);portd=0; snd();portd=15; snd();  porte.b1=1;delay_ms(100);
        portd=0x3;  }
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void set_length_out(char edp,char lnht){bdnbuff[(edp*8)+1]=lnht; }
    void set_length_in(char edp,char lnht){bdnbuff[(edp*8)+5]=lnht;  }
     void  set_buff_add(char edp){bdnbuff[(edp*8)+2]=edp*0x80; bdnbuff[(edp*8)+6]=edp*0x80;  bdnbuff[(edp*8)+3]=5; bdnbuff[(edp*8)+7]=6;}
   
   
   
     //aff_req(); delay_ms(5000);clr_aff(); aff_req();
void main() {  while (1){
 init_sys(); set_length_out(0,8); set_length_in(0,8);set_buff_add(0);      set_length_out(1,8); set_length_in(1,8);  set_buff_add(1);

   enumaration();
}    }