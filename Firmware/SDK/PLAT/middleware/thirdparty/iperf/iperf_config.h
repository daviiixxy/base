#ifndef __IPERF_CONFIG_H__
#define __IPERF_CONFIG_H__

/******************************************************
 *                    Constants
 ******************************************************/

#define MAX_WIN_SIZE (20*1024)

/* Private macro */
#define IPERF_DEFAULT_PORT  5001 //Port to listen

#define IPERF_HEADER_VERSION1 0x80000000
#define IPERF_DEFAULT_UDP_RATE (1024 * 1024)
#define IPERF_TEST_BUFFER_SIZE (2000)
#define IPERF_DEFAULT_PACKET_SIZE 500
#define IPERF_DEFAULT_SEND_TIME 10
#define IPERF_MAX_SEND_RCV_TIME 0XFFFF
#define IPERF_DEFAULT_REPORT_INTERVAL 10
#define IPERF_TOTAL_SEND_MAX 0X7FFFFFF
#define IPERF_DEFAULT_PAYLOAD_SIZE 1372
#define IPERF_DEFAULT_TPT   (1*1024)   //1KBps = 8 kbps
#define IPERF_SERVER_MAX_LISTEN_NUM 10

/* for iperf task */
#define IPERF_THREAD_STACKSIZE 1024

#define IPERF_THREAD_PRIO 16

#define IPERF_COMMAND_BUFFER_NUM (18)
#define IPERF_COMMAND_BUFFER_SIZE (20) // 4 bytes align

#define IPERF_SERVER_RECEIVE_TIMEOUT 10

#define IPERF_DEBUG_RECEIVE     (1<<0)
#define IPERF_DEBUG_SEND        (1<<1)
#define IPERF_DEBUG_REPORT      (1<<2)

#define IPERF_DEFAULT_SEND_NUM   1000

//IPERF_DEBUG_ENABLE
//IPERF_DEBUG_INTERNAL

#endif

