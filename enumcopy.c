                             char EDP,eps,ofs,ufs, BDn,daTa=0,dir=1,rem,u,cnt,udrs,size,enm,togl,togl1,uart_rd,stp=1,put=0;
                      char output[65];
           extern void set_length_in( char edp,char lnht);
           extern void set_length_out(char edp,char lnht);
           extern void  set_buff_add(char edp) ;
           extern char cynt,byt,i,lenght;
           extern unsigned char bdnbuff[16]     ;
           extern unsigned char readbuff[0x80]  ;
           extern unsigned char writebuff[0x80] ;
           extern unsigned char readbulk[0x80]  ;
           extern unsigned char writebulk[0x80] ;
           extern   unsigned char affbuff[100] ;
           extern void conv_char(char cr)   ;
           extern  void clr_aff();
            extern void aff_req();
           extern char devic_disc [];
           extern char conf_disc [];
           extern char string_disc [];
           extern char stringoz_disc [];
           extern char string1_disc [];
          
           extern void sn_devic0();
           extern void sn_devicQ();
           extern  void sn_conf();
           extern  void sn_conf9();
           extern  void sn_devic();
           extern void sn_string();
           extern void sn_string1();
           extern void sn_string2();
           extern void sn_report();

           extern void sn_conf_2();
           extern void sn_conf9_2();
           

void new_Trans(char ep,char len){UIR=0;   //ustat=0;
   set_length_out( ep,len );set_length_in( ep,len );
  for(i=0;i<8;i++){readbuff[i]=0;}
     }

void usb_init(){UADDR=0; ustat=0;  dir=0; UCFG=0x14;UIE=0;UIR=0;UCON=0x8;  stp=0;
daTa=0;
  while(UCON.B5);  UIE=0;UIR=0; UEP0=0X16 ;UEP1=0X16 ;  }



void clear_ternif(){ while( UIR.b3  ){UIR.b3=0;} }

void get_ACK(){ while( !UIR.b3  );}

/*void SUBMEET_EDP_dr_stl(char ep,char dr,char st)  {UCON.B4=0;
dr.b0=!dr.b0; EDP=(ep*8)+(dr*4) ;BDn=  0x8+(daTa*0x40)+(st*0x4);
 bdnbuff[EDP]= BDn;  bdnbuff[EDP].b7=1;
 if(st==0){while( bdnbuff[EDP].B7 );}}

void SUBMEET_EDP_dr_stl2(char ep,char dr,char st)  {UCON.B4=0; dr.b0=!dr.b0;
 bdnbuff[(ep*8)+(dr*4)]=0x80+(daTa*0x40)+(st*0x4);
 if(st==0){while( bdnbuff[(ep*8)+(dr*4)].B7 );}}*/

  ////////////////////////////////////////////////////////////////////////
void SET_IN_EDP_stl(char ep,char st)  {//UCON.B4=0;
EDP=(ep*8)+4 ;BDn=  0x8+(daTa*0x40)+(st*0x4);
 bdnbuff[EDP]= BDn;  bdnbuff[EDP].b7=1;UCON.B4=0;
 if(st==0){while( bdnbuff[EDP].B7 );}}

void GET_OUT_EDP_stl(char ep,char st)  {
EDP=(ep*8) ;BDn=  0x8+(daTa*0x40)+(st*0x4);
 bdnbuff[EDP]= BDn;  bdnbuff[EDP].b7=1; UCON.B4=0  ;
 if(st==0){while( bdnbuff[EDP].B7 );}}

void Up_ep_byte_ofs_len(char ep,char vector[],char offset,char count){ if(count!=8){ set_length_in( ep,count );}
for(i=0 ;i<count;i++){eps=i+( ep*0x80);ofs= i+offset; writebuff[ eps] =vector[ofs]; }}


void Up_ep_Vect(char ep,char vector[]){ daTa=1;size=sizeof(vector); rem =size;//rem=  vector[0];
cnt=8;
for(u=0;u<=size/8;u++){if(rem<8){cnt=rem; set_length_in( ep,cnt );  }else{rem=rem-8;}
 while( !UCON.B4 );for(i=0 ;i<cnt;i++){ writebuff[i+( ep*0x80) ] =vector[i+(8*u)]; }
   SET_IN_EDP_stl(ep,0);   get_ACK();   clear_ternif(); daTa=(daTa+1)%2;}   }



void Up_ep_Vect2(char ep,char vector[]){ daTa=1;size=sizeof(vector)/8; rem =sizeof(vector);//rem=  vector[0];
cnt=8;
for(u=0;u<=size;u++){ufs=8*u;if(rem<8){ cnt=rem; set_length_in( ep,cnt );  }else{rem=rem-8;}
 Up_ep_byte_ofs_len(ep,vector,ufs,cnt); SET_IN_EDP_stl(ep,0);get_ACK();   clear_ternif();
 if(daTa=1){daTa=0;}else{ daTa=1;  }
 } }
  char write_byte(char rt){ if(rt>=0xa){return rt+0x37;}else{return rt+0x30;   } }

 
 void UART1_Writer(char cr){int cc=cr; cc= (cc&0xf0)/0x10; UART1_Write(write_byte(cc)); cr=cr&0xf; UART1_Write(write_byte(cr));    }

void get_discINS(){ output[0]=0;


              put=0;
          // while  (!UART1_Data_Ready());      UART_Read_Text(output, "*", 64);    while(UART1_Data_Ready() );
          // UART1_Write_Text("step to"); UART1_Writer(output[0]);
          while (put==0) {
  if (UART1_Data_Ready() == 1) {          // if data is received
    UART1_Read_Text(output, "**", 65);    // reads text until 'OK' is found
    UART1_Write_Text(output);put=0xff;             // sends back text
 }
}

      }

void SETUP_STaGE () { put++;stp=output[put];new_Trans(0,8);  daTa=0; GET_OUT_EDP_stl(0,0);  get_ACK();   clear_ternif();
 }


 void stall_send(){daTa=0; SET_IN_EDP_stl(0,1);  while(!UIR.B5); while(UIR.B5){UIR.B5=0;} while(UEP0.B0){UEP0.B0=0;}}

 void ack_hnd(){  daTa=1;                                         GET_OUT_EDP_stl(0,0);                get_ACK();   clear_ternif() ;}
 void snd_hnd(){  daTa=1;                                         SET_IN_EDP_stl(0,0);                 get_ACK();   clear_ternif() ;}

 void ack_hnd1(){  daTa=1;                                         GET_OUT_EDP_stl(1,0);                get_ACK();   clear_ternif() ;}
 void snd_hnd1(){  daTa=1;                                         SET_IN_EDP_stl(1,0);                 get_ACK();   clear_ternif() ;}
 ////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////
void enumaration()
{  UART1_Init(9600); UART1_Write(0xaa);UART1_Write(0xaa); get_discINS();
usb_init() ;



 //new_Trans(0,8);
  //     daTa=0;                                        GET_OUT_EDP_stl(0,0); /*aff_req( );*/  get_ACK();   clear_ternif() ;

 //      daTa=1;Up_ep_byte_ofs_len(0,devic_disc,0,8);   SET_IN_EDP_stl (0,0);                  get_ACK();   clear_ternif() ;
       // THERE IS NO HANDSHAKE STAGE INSTEAD HOST SENDS DIRECTLY A SET ADDR

 //      daTa=0;                                        GET_OUT_EDP_stl(0,0);udrs=readbuff[2];

  //    daTa=1;   set_length_in( 0,0 ) ;               SET_IN_EDP_stl(0,0);   //DEVICE MUST SEND ZLP TO HANDSHAKE SET ADRESS REQ



  enm=1;
 while(enm==1){
 SETUP_STaGE ();
 if(stp==0x00){
       UART1_Write(readbuff[0]);  UART1_Write(readbuff[1]);  UART1_Write(readbuff[3]);   UART1_Write(readbuff[2]);
       UART1_Write(readbuff[5]);  UART1_Write(readbuff[4]);  UART1_Write(readbuff[7]);   UART1_Write(readbuff[6]);
      UART1_Write(readbuff[uir]);UART1_Write(readbuff[ustat]); UART1_Write(0x2a);UART1_Write(0x2a);
       enm=0xff; }
  
  else if(stp==0xad)
    { udrs=readbuff[2]; set_length_in( 0,0 ) ;  snd_hnd();UADDR=udrs; }
 
 else if(stp==0x10)
   //if((0x80==readbuff[0])&&(0x6==readbuff[1])&&(0x1==readbuff[3])&&(0x0==readbuff[2])&&( ((readbuff[7]*0x100)+readbuff[6])>=18 ))
  {sn_devic0(); }

 else if(stp==0x11)
   //if((0x80==readbuff[0])&&(0x6==readbuff[1])&&(0x1==readbuff[3])&&(0x0==readbuff[2])&&( ((readbuff[7]*0x100)+readbuff[6])>=18 ))
  {sn_devicQ(); ack_hnd();}
  
 else if(stp==0x18)
   //if((0x80==readbuff[0])&&(0x6==readbuff[1])&&(0x1==readbuff[3])&&(0x0==readbuff[2])&&( ((readbuff[7]*0x100)+readbuff[6])>=18 ))
  {sn_devic(); ack_hnd();}
  
  
  else if(stp==0x20)
 //else if((0x80==readbuff[0]  )&& (0x6==readbuff[1]) &&(0x2==readbuff[3])&&(0x0==readbuff[2])&&(((readbuff[7]*0x100)+readbuff[6])>=9) )
  {  sn_conf9();ack_hnd();}

else if(stp==0x29)
 //else if((0x80==readbuff[0]  )&& (0x6==readbuff[1]) &&(0x2==readbuff[3])&&(0x0==readbuff[2])&&(((readbuff[7]*0x100)+readbuff[6])>=41) )
  {  sn_conf();
  ack_hnd();}

   else if(stp==0x2f)
 //else if((0x80==readbuff[0]  )&& (0x6==readbuff[1]) &&(0x2==readbuff[3])&&(0x0==readbuff[2])&&(((readbuff[7]*0x100)+readbuff[6])>=9) )
  {  sn_conf_2();ack_hnd();}

else if(stp==0x21)
 //else if((0x80==readbuff[0]  )&& (0x6==readbuff[1]) &&(0x2==readbuff[3])&&(0x0==readbuff[2])&&(((readbuff[7]*0x100)+readbuff[6])>=41) )
  {  sn_conf9_2();
  ack_hnd();}


else if(stp==0x30)
 //else if((0x80==readbuff[0]  )&& (0x6==readbuff[1]) &&(0x3==readbuff[3])&&(0x0==readbuff[2])&&(((readbuff[7]*0x100)+readbuff[6])==0x800) )
 { sn_string(); ack_hnd();}

else if( stp==0x31)
 //else if((0x80==readbuff[0]  )&& (0x6==readbuff[1]) &&(0x3==readbuff[3])&&(0x1==readbuff[2])&&(((readbuff[7]*0x100)+readbuff[6])==0x800) )
 { sn_string1(); ack_hnd(); }


 else if(stp==0x32)
 //else if((0x80==readbuff[0]  )&& (0x6==readbuff[1]) &&(0x3==readbuff[3])&&(0x2==readbuff[2])&&(((readbuff[7]*0x100)+readbuff[6])==0x800) )
{ sn_string2(); ack_hnd();}
 //////////////////////////////////////////////////
 else if(stp==0x35)
 //else if((0x80==readbuff[0]  )&& (0x6==readbuff[1]) &&(0x3==readbuff[3])&&(0x2==readbuff[2])&&(((readbuff[7]*0x100)+readbuff[6])==0x800) )
{         sn_string2(); ack_hnd();enm=5;}
 
 else if(stp==0x36)
 //else if((0x80==readbuff[0]  )&& (0x6==readbuff[1]) &&(0x3==readbuff[3])&&(0x2==readbuff[2])&&(((readbuff[7]*0x100)+readbuff[6])==0x800) )
{         sn_string2(); ack_hnd();enm=6;}
 
 else if(stp==0x34)
 //else if((0x80==readbuff[0]  )&& (0x6==readbuff[1]) &&(0x3==readbuff[3])&&(0x2==readbuff[2])&&(((readbuff[7]*0x100)+readbuff[6])==0x800) )
{

sn_string2(); ack_hnd();enm=4;}


else if(stp==8)
 //else if((0x21==readbuff[0]  )&& (0xa==readbuff[1]) &&(0==readbuff[3])&&(0==readbuff[2]) &&(((readbuff[7]*0x100)+readbuff[6])==0))
 {  set_length_in( 0,0 ) ;  snd_hnd();}


else if(stp==9)
 //else if((0x81==readbuff[0]  )&& (0x6==readbuff[1]) &&(0x22==readbuff[3])&&(0x0==readbuff[2])&&(((readbuff[7]*0x100)+readbuff[6])==0x61) )
  {  sn_report();ack_hnd();}


  else if(stp==0xe)
  { enm=5;}


else if(stp==0xc) {stall_send();}
 //else if{stall_send();}}
 
 else if(stp==0xd)
  { enm=4;}
  
 else if(stp==0xdd) { enm=3;}
  
     }
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////vendor c trans////////////////////////////////////////////////////////////////////////////
  if(enm==3){
        UART1_Write(0x0); UART1_Write(0x3);
  while(enm==3){
daTa=1;Up_ep_byte_ofs_len(0,readbuff,0,8);   SET_IN_EDP_stl (0,0);                get_ACK();   clear_ternif() ;
 ack_hnd();

UART1_Write(readbuff[0]);  UART1_Write(readbuff[1]);  UART1_Write(readbuff[3]);   UART1_Write(readbuff[2]);
UART1_Write(readbuff[5]);  UART1_Write(readbuff[4]);  UART1_Write(readbuff[7]);   UART1_Write(readbuff[6]);  // while(1);
 new_Trans(0,8);  daTa=0; GET_OUT_EDP_stl(0,0);  get_ACK();   clear_ternif(); }


   }



///////////////////////////////hid////////////////////////////////////////////////////////////////////////////
    //bulk begain
if(enm==4){   // UART1_Write(0x0); UART1_Write(0x4);

  bdnbuff[0xc]=0x8;bdnbuff[8]=0x88;
  ucon.b4=0;
  togl=0x8; togl1=0x8;


/////////////////////////////***************************************************************

    while(enm==4){
  if(bdnbuff[8].b7==0){get_ACK();   clear_ternif();   UART1_Write(ustat);
     // for(i=0;i<8;i++){ if(readbuff[0x80+i]!=0){conv_char(readbuff[0x80+i]);}}
      for(i=0;i<8;i++){ if(readbuff[0x80+i]!=0){UART1_Write(readbuff[0x80+i]);} }
  while(bdnbuff[0xc].b7==1);   
   togl.b6=!togl.b6;bdnbuff[8]=togl;bdnbuff[8].b7=1;ucon.b4=0;}
    
    else if(bdnbuff[8].b7==1){
  if (UART_Data_Ready() == 1) {          // if data is received
    UART_Read_Text(output,"**",65);
    for(i=0;i<8;i++){ writebuff[0x80+i]=output[i];}
     while(bdnbuff[0xc].b7==1);
     togl1.b6=!togl1.b6;bdnbuff[0xc]=togl1;bdnbuff[0xc].b7=1;ucon.b4=0;
                     clear_ternif() ;
      for(i=0;i<65;i++){  output[i]=0 ;} }  }
    }}


    //////////////////////////////////////////////////////////******************************************

    if(enm==5){  daTa=0;   //new_Trans(0,8);  daTa=0; GET_OUT_EDP_stl(0,0);  get_ACK();   clear_ternif();
                  UART1_Write(0xb);  UART1_Write(0xb);UART1_Write(ustat); UART1_Write(uir);
             writebuff[0x80]=0xb;  writebuff[0x81]=0xb;   writebuff[0x82]=0xb; writebuff[0x83]=0xb;
              writebuff[0x84]=0xc;  writebuff[0x85]=0xc;   writebuff[0x86]=0xc; writebuff[0x87]=0xc;
                 writebuff[0x88]=0xc;  writebuff[0x89]=0xc;   writebuff[0x8a]=0xc; writebuff[0x8b]=0xc;
    /*while(enm==5){      new_Trans(1,8);  daTa=0; GET_OUT_EDP_stl(1,0);  get_ACK();   clear_ternif();
daTa=1;Up_ep_byte_ofs_len(0,readbuff,1,8);   SET_IN_EDP_stl (1,0);                get_ACK();   clear_ternif() ;
 ack_hnd1(); */
  while (enm==5){  new_Trans(1,8);   GET_OUT_EDP_stl(1,0);  get_ACK();   clear_ternif();
             //bdnbuff[0xc]= 0x88;  bdnbuff[0xc].b7=1;UCON.B4=0;   while(  bdnbuff[0xc].b7==1);
             

                 
                 SET_IN_EDP_stl (1,0);
             
           get_ACK();   clear_ternif(); daTa.b0=!daTa.b0;
  for (i=0x80;i<0x8c;i++){UART1_Write(readbuff[i]);readbuff[i]=0; }
  UART1_Write(ustat);UART1_Write(uir); //



//new_Trans(0,8);  daTa=0; GET_OUT_EDP_stl(0,0);  get_ACK();   clear_ternif(); 
}   }

    if(enm==6){  daTa=0;   //new_Trans(0,8);  daTa=0; GET_OUT_EDP_stl(0,0);  get_ACK();   clear_ternif();
                  UART1_Write(0xb);  UART1_Write(0xb);UART1_Write(ustat); UART1_Write(uir);
             writebuff[0x80]=0xb;  writebuff[0x81]=0xb;   writebuff[0x82]=0xb; writebuff[0x83]=0xb;
              writebuff[0x84]=0xc;  writebuff[0x85]=0xc;   writebuff[0x86]=0xc; writebuff[0x87]=0xc;
                 writebuff[0x88]=0xc;  writebuff[0x89]=0xc;   writebuff[0x8a]=0xc; writebuff[0x8b]=0xc;
    /*while(enm==5){      new_Trans(1,8);  daTa=0; GET_OUT_EDP_stl(1,0);  get_ACK();   clear_ternif();
daTa=1;Up_ep_byte_ofs_len(0,readbuff,1,8);   SET_IN_EDP_stl (1,0);                get_ACK();   clear_ternif() ;
 ack_hnd1(); */
  while (enm==6){  new_Trans(1,8);   GET_OUT_EDP_stl(1,0);  get_ACK();   clear_ternif();
             //bdnbuff[0xc]= 0x88;  bdnbuff[0xc].b7=1;UCON.B4=0;   while(  bdnbuff[0xc].b7==1);

                 UART1_Write(0xc);  UART1_Write(0xc);
                   while (UART_Data_Ready()!= 1);           // if data is received
    UART_Read_Text(output,"**",12);
    for(i=0;i<12;i++){ writebuff[0x80+i]=output[i];}

                 SET_IN_EDP_stl (1,0);

           get_ACK();   clear_ternif(); daTa.b0=!daTa.b0;
  for (i=0x80;i<0x8c;i++){UART1_Write(readbuff[i]);readbuff[i]=0; }
  UART1_Write(ustat);UART1_Write(uir); //



//new_Trans(0,8);  daTa=0; GET_OUT_EDP_stl(0,0);  get_ACK();   clear_ternif();
}   }

   //////////////////////////////////////////////////////////******************************************

UCON=0;portd=0;delay_ms(3000); }//aff_req( );