         extern  void Up_ep_byte_ofs_len(char ep,char vector[],char offset,char count);
         extern char  daTa;
          extern void SET_IN_EDP_stl(char ep,char st) ;
          extern void      get_ACK();
          extern void      clear_ternif();
           char devic_disc []={ 18,1,0,2,0,0,0,8,0x78,0x19,1,0X23,0,1,1,2,0,1} ;
           char devic_discQ []={ 18,6,0,2,0,0,0,8,0,0} ;
           char  conf_disc []={9,2,41,0,1,1,0,0xc0,
                               0x32,9,4,0,0,2,3,0,
                               0,0,9,0x21,1,1,0,1,
                               0x22,0x21,0,7,5,0x81,3,0x40,
                               0,1,7,5,1,3,0x40,0,       1   } ;
          char string_disc []={4,3,9,4}  ;
          char stringoz_disc []={0xc,3,0x49,0,0x53,0,0x4c,0,0x41,0,0x4d,0}  ;
          char string1_disc  []={0xc,3,0x55,0,0x53,0,0x42,0,0x20,0,0x4C,0}  ;
          char string_report []={6,0,0xff,9,1,0xa1,1,0x19,
                                 1,0x29,0x40,0x15,0,0x26,0xff,0,
                                 0x75,8,0x95,8,0x81,2,0x19,1,
                                 0x29,0x40,0x75,8,0x95,8,0x91,2,  0xc0}  ;
  void sn_devic0(){
       daTa=1;Up_ep_byte_ofs_len(0,devic_disc,0,8);   SET_IN_EDP_stl (0,0);                get_ACK();   clear_ternif() ; }
 
  void sn_devicQ(){
      daTa=1;Up_ep_byte_ofs_len(0,devic_discQ,0,8);    SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif();
      daTa=0;Up_ep_byte_ofs_len(0,devic_discQ,8,2);    SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif(); }
void sn_devic(){
       daTa=1;Up_ep_byte_ofs_len(0,devic_disc,0,8);   SET_IN_EDP_stl(0,0) ;                get_ACK();   clear_ternif();
       daTa=0;Up_ep_byte_ofs_len(0,devic_disc,8,8);   SET_IN_EDP_stl(0,0) ;                get_ACK();   clear_ternif();
       daTa=1;Up_ep_byte_ofs_len(0,devic_disc,16,2);  SET_IN_EDP_stl(0,0) ;                get_ACK();   clear_ternif() ;  }

 void sn_conf(){
      daTa=1;Up_ep_byte_ofs_len(0,conf_disc,0,8);    SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif();
      daTa=0;Up_ep_byte_ofs_len(0,conf_disc,8,8);    SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif();
      daTa=1;Up_ep_byte_ofs_len(0,conf_disc,16,8);   SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif() ;

      daTa=0;Up_ep_byte_ofs_len(0,conf_disc,24,8);   SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif();
      daTa=1;Up_ep_byte_ofs_len(0,conf_disc,32,8);   SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif() ;
      daTa=0;Up_ep_byte_ofs_len(0,conf_disc,40,1);   SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif();}


  void sn_conf9(){
      daTa=1;Up_ep_byte_ofs_len(0,conf_disc,0,8);    SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif();
      daTa=0;Up_ep_byte_ofs_len(0,conf_disc,8,1);    SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif(); }


void sn_string(){ 
      daTa=1;Up_ep_byte_ofs_len(0,string_disc,0,4);    SET_IN_EDP_stl(0,0);                 get_ACK();   clear_ternif(); }
      
void sn_string1(){
      daTa=1;Up_ep_byte_ofs_len(0,stringoz_disc,0,8);  SET_IN_EDP_stl(0,0);                get_ACK();   clear_ternif(); 
      daTa=0;Up_ep_byte_ofs_len(0,stringoz_disc,8,4);  SET_IN_EDP_stl(0,0);                get_ACK();   clear_ternif();}
      
void sn_string2(){
      daTa=1;Up_ep_byte_ofs_len(0,string1_disc,0,8);  SET_IN_EDP_stl(0,0);                get_ACK();   clear_ternif();
      daTa=0;Up_ep_byte_ofs_len(0,string1_disc,8,4);  SET_IN_EDP_stl(0,0);                get_ACK();   clear_ternif();}

 void sn_report(){
      daTa=1;Up_ep_byte_ofs_len(0,string_report,0,8);    SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif();
      daTa=0;Up_ep_byte_ofs_len(0,string_report,8,8);    SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif();
      daTa=1;Up_ep_byte_ofs_len(0,string_report,16,8);   SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif() ;

      daTa=0;Up_ep_byte_ofs_len(0,string_report,24,8);   SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif();
      daTa=1;Up_ep_byte_ofs_len(0,string_report,32,1);   SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif(); }
     ///////////////////////////////////
      char  conf2_disc []={    9,2,32,0,1,2,0,0xc0,0x32,
                               9,4,0,0,2,0xff,0,0,0,
                               7,5,0x81,2,0x40,0,0,
                               7,5,1   ,2,0x40,0,0   } ;
                               
                               
  void sn_conf_2(){
      daTa=1;Up_ep_byte_ofs_len(0,conf2_disc,0,8);    SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif();
      daTa=0;Up_ep_byte_ofs_len(0,conf2_disc,8,8);    SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif();
      daTa=1;Up_ep_byte_ofs_len(0,conf2_disc,16,8);   SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif() ;

      daTa=0;Up_ep_byte_ofs_len(0,conf2_disc,24,8);   SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif();
      }


  void sn_conf9_2(){
      daTa=1;Up_ep_byte_ofs_len(0,conf2_disc,0,8);    SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif();
      daTa=0;Up_ep_byte_ofs_len(0,conf2_disc,8,1);    SET_IN_EDP_stl(0,0);                  get_ACK();   clear_ternif(); }