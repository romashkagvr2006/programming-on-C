#include <stdio.h>
#include "..\INC\Net_Config.h"
#include "..\APP\DEFINITION.h"

// ----------------------------------------------- Variables

//extern struct SB_param ;

struct SB_param{
  U32  FlashPage_FF;
  U8   lcd_KP[8][8];
	U8   lcd_RR[8][8];
	U8   lcd_GG[8][8];
  } ;


	extern U16 	clb_time;
	
extern float Temperatura;
extern	struct SB_param	SB_param;
	

extern int   DM9000_VendorID;
extern int   DM9000_ProductID;
extern int   DM9000_IO_mode;


extern float NAK_X;
extern float NAK_Y;
extern float NAK_S;

extern float OTKL_X;
extern float OTKL_Y;
extern float OTKL_Z;
extern float PERIOD;

extern  U8 n_sb;
extern  U32 st_ZAPROS_ON;

extern BOOL ZPR;
extern BOOL  DATCHIK;
extern BOOL  HIDER;
extern U8 flag1;
extern U8 flag2;
extern U8 flag4;
extern U16 	m_time_st;
extern U8 	m_time;
extern U32 st_data_uart3;
extern U32 st_adr_serial_3_in;
extern U32 max_uart1;
extern U8 receive_start_3;
extern U8 UART_2_in_CRC;
extern U16 	st_hider;

extern U32 n_datchik;
extern U32 cykl;

extern U8 mark;
extern U8 mark_s;
extern U8    command_src;
extern U8    command_complete;
extern U8    command_escape;
extern U32   command_phase;
//extern U8 test_timer;

//extern U8	 number_of_chenal;
extern U32   file_data_count;
extern U32   timeout;
//extern U32	 number_sinchroimpuls; 
extern U32   pCommand_cgi;
extern U32   pCommand_next;
extern U32   pLog_txt;
extern U32   pLog_txt_end;
//extern U8    command_src;
//extern U8    command_complete;
//extern U8    command_escape;
//extern U32   command_phase;
extern U8    flash_changed;
extern U8    LED1_blink;

extern S16 parametr[];


//extern U8	GPIO;
//extern U8	ADCON;
//extern U8   DRATE;
//extern U8   amp_rate;
extern U16  data_1ms;
//extern U16   n_data;
//extern U16   data_rate;
//extern float  delta_data_rate;
//extern U16   AD_rate;
//extern U16   size;
//extern U16   tcp_max;

//extern U32   musor;

extern S32* paket_adr_X;
extern S32* paket_adr_Y;
extern S32* paket_adr_Z;
extern S32* out_paket_adr_X;
extern S32* out_paket_adr_Y;
extern S32* out_paket_adr_Z;
extern U32 delta_time_write;

extern U32   default_addr;
extern U32   default_v1;
extern U32   default_v2;

extern U32   ex_ram_buf[1];   

extern FILE  * fi;
extern FILE  * fo;

extern float AD_T;
extern float AD_popr;	
extern float f_clb;//[];
extern float a_clb;
extern float out_amp_s[];
extern U8 faza[];
extern float kp[];
extern float kp_db[];
extern float cnrk[];

extern  unsigned long long sequence_number;
extern  unsigned long long highest_number;

extern S32* paket_adr_parametr_1;		// Поток на запись 
extern S32* paket_adr_parametr_2;
extern S32* paket_adr_parametr_3;
extern S32* paket_adr_parametr_4;
extern S32* paket_adr_parametr_5;

extern S32* out_paket_adr_parametr_1;	// Поток на передачу
extern S32* out_paket_adr_parametr_2;
extern S32* out_paket_adr_parametr_3;
extern S32* out_paket_adr_parametr_4;
extern S32* out_paket_adr_parametr_5;

extern S32 data_parametr_1_1[];
extern S32 data_parametr_2_1[];
extern S32 data_parametr_3_1[];
extern S32 data_parametr_4_1[];
extern S32 data_parametr_5_1[];

extern S32 data_parametr_1_2[];
extern S32 data_parametr_2_2[];
extern S32 data_parametr_3_2[];
extern S32 data_parametr_4_2[];
extern S32 data_parametr_5_2[];

extern float parametr_1;
extern float parametr_2;
extern float parametr_3;
extern float parametr_4;
extern float parametr_5;


// ----------------------------------------------- Arrays

//extern U8   lcd_text[];

extern U32 FlashPage_BB[];

extern float naklon[];
extern U8 spisok[8][6];

extern U8 SEYSM_DATA[];
extern U8 DATA_UART3[];
extern U8 HIDER_UART3[];

extern U8 acknack_buf[];

extern char n_GPS_fild[];
extern char GPS_string[];
extern char crc_string[];

extern U8 status_data[];
extern U8	Ch_1_0_data[];
extern U8	Ch_2_0_data[];
extern U8	Ch_3_0_data[];

extern U8 FSUK_KOMANDA[];
extern U8 FSUK_DATA[];

extern S32 data_X_1[];
extern S32 data_Y_1[];
extern S32 data_Z_1[];
extern S32 data_X_2[];
extern S32 data_Y_2[];
extern S32 data_Z_2[];

extern S32 data_X[];
extern S32 data_Y[];
extern S32 data_Z[];

extern S32 clb_data_X[];
extern S32 clb_data_Y[];
extern S32 clb_data_Z[];

extern U8  clb_init;
extern U8  r_clb;
//extern U32 t_pila[];

extern U8 temp_f[];
extern U8 time [];
extern U8  *adr_buf;
extern U8  *adr_ram;
extern U8  *out_udp_adr;

extern U8 number_ack;
extern U8 rep_servis_frame[];
extern U8 asc_servis_frame[];
extern U8 servis_frame[];
extern signed int  paket_1[];
extern signed int  paket_2[];

extern char  Log_txt       [LOG_SZ];

extern char  Command_cgi   [CMD_SZ];
extern  U32  FlashPage     [PAGE_SZ/4];

extern  char html_buf      [HTMLBUF_SZ];
extern  U32  phtml_buf;

extern  U32  FlashPage_FF[48];
// ----------------------------------------------- Constants

extern U8 dev_name[];

extern const char html_settings_head[];
extern const char html_fifo_head[]; 
extern const char html_flash_head[]; 
extern const char html_ram_head[]; 
extern const char html_table_tail[]; 
extern const char short_help[]; 

extern U8 own_hw_adr[];
extern U8 lhost_name[];
extern LOCALM localm[];

// ----------------------------------------------- Function
extern void slep(void);
extern void zapros(void);
extern void Termostat(void);
extern void Check_Line(void);
extern void write_time(void);
extern void ampl(void);
extern float CL_in (U8 ch);
extern void pusk(void);
extern void set_cnrk(U8 i);
extern void set_clb_f(void);
extern void set_name(void);
extern void exchange_paket(void);
extern void set_filtr(void);
extern void set_time_mem(void);
extern void set_ampl(void);
extern void set_data_parametr(void);
extern void set_protokol(void);
extern void Init_Set(void);
extern void set_bod_rate(void);
extern void set_data_rate(void);
extern void get_rep_frame (void);
extern void acknack(void);
extern void GPS_time (void);
extern char getchar1 (void);
extern void filtr(void);
extern void filtr_1(void);
extern void init_info(void);
extern void check_frame(unsigned char rw, char* buffer, unsigned int buffer_length);
extern void make_data_kadr(void);
extern void make_request(void);
extern void init_frame_request(void);
extern unsigned long crctablefast (U8 *p, U32 len);

extern void send_data (void);
extern void reset_ads (void);
extern void selfcal(void);
extern void sync_ad(void);
extern void  config_ad(void);
extern void begin_ad(void);
extern void data_da(void);
extern void check_up_flags(void);
extern void RTC_Poll (void);

extern void read_ad(void);
extern void syscal(void);
extern void prepare(void);

extern void SPIInit(void);
extern void spi_send_0 (unsigned char n_bait);
extern void spi_resiv (unsigned char n_bait);
extern void spi1_send (void);

extern void wait_ms(U32 ms);

extern int  std_file_open (const char *name, int openmode);
extern int  std_file_read (int fh,       U8 *buf, U32 len, int mode);
extern int  std_file_write(int fh, const U8 *buf, U32 len, int mode);
extern int  std_file_close(int fh);

extern void var_save(void);
extern void wait_ms(U32 ms);
extern void set_timeout(U32 time);
extern U32  timeout_expired(void);
extern int  getkey (void);
extern int  getline (void);
extern int  sendchar (int ch);
extern void dump_frame(unsigned char rw, char* buffer, unsigned int buffer_length);
//extern int  fat_init (void);
extern void var_save(void);
extern U32  get_code_check(void);

extern void Init_Hal    (void);
extern void Init_VAR    (void);
extern void Init_SD     (void);

extern void spi_SD_init   (void);
extern void restore_spi_SD(void);

extern void Init_Dev           (void);
extern void Init_Var_Dev       (void);
extern void Start_Dev          (void);
extern void Stop_Dev           (void);
extern void Main_Dev           (void);
extern void Data_Open_Dev      (void);
extern int  Data_Read_Bin_Dev  (U8 *buf, U32 len);
extern void Data_Read_Htm_Dev  (void);
extern void Data_Close_Dev     (void);
extern char Data_Dev_Ready     (void);
extern void Test_Dev           (void);

extern void RAM_Test           (void);

extern void Init_Console(void);
extern void Timer_Poll  (void);
extern void Main_Console(void);

extern void Process_Command(void);
extern void process_cmd_start(U8 src, char * buf);
extern void process_cmd_stop(void);

extern void put_log_char(char ch);
extern char get_log_char(void);
extern void print_log(char * txt, char tp, void * v); 

extern void wr_ex_ram(U32 addr,U8 b);
extern U8   rd_ex_ram(U32 addr);
extern void RTL_test(void);
extern void Driver_Output_Enable(void);
extern void UART1_Isr(void)__irq;
//extern void Boot(void);

//extern void Boot_arm(void);
//extern void boot_arm_erase_flash(void);
//extern int boot_arm_write_flash(U8 *buf, U32 len);

//extern struct sub_header_frame;
