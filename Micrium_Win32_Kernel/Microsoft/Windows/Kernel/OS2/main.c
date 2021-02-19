/*
*********************************************************************************************************
*                                            EXAMPLE CODE
*
*               This file is provided as an example on how to use Micrium products.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only. This file can be modified as
*               required to meet the end-product requirements.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can find our product's user manual, API reference, release notes and
*               more information at https://doc.micrium.com.
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                              uC/OS-II
*                                            EXAMPLE CODE
*
* Filename : main.c
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_mem.h>
#include  <os.h>

#include  "app_cfg.h"


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  OS_STK  StartupTaskStk[APP_CFG_STARTUP_TASK_STK_SIZE];

static OS_STK Task1Stk[APP_CFG_STARTUP_TASK_STK_SIZE];

static OS_STK Task2Stk[APP_CFG_STARTUP_TASK_STK_SIZE];

static OS_STK Task3Stk[APP_CFG_STARTUP_TASK_STK_SIZE];

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

//static  void  StartupTask (void  *p_arg);

static void Task1(void *p_arg);

static void Task2(void *p_arg);

static void Task3(void *p_arg);

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*
* Notes       : none
*********************************************************************************************************
*/

OS_EVENT* event;
OS_ERR err;

int  main (void)
{
#if OS_TASK_NAME_EN > 0u
    CPU_INT08U  os_err;
#endif


    //CPU_IntInit();

    //Mem_Init();                                                 /* Initialize Memory Managment Module                   */
    //CPU_IntDis();                                               /* Disable all Interrupts                               */
    //CPU_Init();                                                 /* Initialize the uC/CPU services                       */

    OSInit();                                                   /* Initialize uC/OS-II                                  */
	event = OSSemCreate(1);
    OSTaskCreateExt(Task1,/*����ָ��*/                               /* Create the startup task                              */
        0,/*��������ʱ���ݵĲ���*/
        &Task1Stk[APP_CFG_STARTUP_TASK_STK_SIZE - 1u],/*ָ���ջ����ջ����ָ��*/
        APP_CFG_STARTUP_TASK_PRIO,/*�������ȼ�*/
        APP_CFG_STARTUP_TASK_PRIO,/*����ID*/
        &Task1Stk[0u],/*��ջ�ײ�ָ��*/
        APP_CFG_STARTUP_TASK_STK_SIZE,/*�����ջ��С*/
        0u,/*�������ݽṹ��ָ�룬��ΪTCB����չ*/
        (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));/*��������������ص���Ϣ*/

	OSTaskCreateExt(Task2,/*����ָ��*/                               /* Create the startup task                              */
		0,/*��������ʱ���ݵĲ���*/
		&Task2Stk[APP_CFG_STARTUP_TASK_STK_SIZE - 1u],/*ָ���ջ����ջ����ָ��*/
		APP_CFG_STARTUP_TASK_PRIO+1,/*�������ȼ�*/
		APP_CFG_STARTUP_TASK_PRIO+1,/*����ID*/
		&Task2Stk[0u],/*��ջ�ײ�ָ��*/
		APP_CFG_STARTUP_TASK_STK_SIZE,/*�����ջ��С*/
		0u,/*�������ݽṹ��ָ�룬��ΪTCB����չ*/
		(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));/*��������������ص���Ϣ*/

	OSTaskCreateExt(Task3,/*����ָ��*/                               /* Create the startup task                              */
		0,/*��������ʱ���ݵĲ���*/
		&Task3Stk[APP_CFG_STARTUP_TASK_STK_SIZE - 1u],/*ָ���ջ����ջ����ָ��*/
		APP_CFG_STARTUP_TASK_PRIO + 2,/*�������ȼ�*/
		APP_CFG_STARTUP_TASK_PRIO + 2,/*����ID*/
		&Task3Stk[0u],/*��ջ�ײ�ָ��*/
		APP_CFG_STARTUP_TASK_STK_SIZE,/*�����ջ��С*/
		0u,/*�������ݽṹ��ָ�룬��ΪTCB����չ*/
		(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));/*��������������ص���Ϣ*/


#if OS_TASK_NAME_EN > 0u
    OSTaskNameSet(         APP_CFG_STARTUP_TASK_PRIO,/*�������ȼ�*/
                  (INT8U *)"Task 1",/*����*/
                           &os_err);/*�쳣*/
	OSTaskNameSet(APP_CFG_STARTUP_TASK_PRIO+1,/*�������ȼ�*/
		(INT8U *)"Task 2",/*����*/
		&os_err);/*�쳣*/
	OSTaskNameSet(APP_CFG_STARTUP_TASK_PRIO+2,/*�������ȼ�*/
		(INT8U *)"Task 3",/*����*/
		&os_err);/*�쳣*/


#endif
    OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II)   */

    while (DEF_ON) {                                            /* Should Never Get Here.                               */
        ;
    }
}


/*
*********************************************************************************************************
*                                            STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'StartupTask()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

//static  void  StartupTask (void *p_arg)
//{
//   (void)p_arg;
//
//    OS_TRACE_INIT();                                            /* Initialize the uC/OS-II Trace recorder               */
//
//#if OS_CFG_STAT_TASK_EN > 0u
//    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
//#endif
//
//#ifdef CPU_CFG_INT_DIS_MEAS_EN
//    CPU_IntDisMeasMaxCurReset();
//#endif
//    
//    APP_TRACE_DBG(("uCOS-II is Running... HOMEWORK BY DQJ\n\r"));
//
//    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
//        OSTimeDlyHMSM(0u, 0u, 0u, 10u);
//		APP_TRACE_DBG(("Time: %d\n\r", OSTimeGet()));
//
//    }
//}

static void Task1(void *p_arg)
{
	int start; //the start time 
	int end; //the end time 
	int toDelay;
	start = 0;
	OSTCBCur->compTime = 1;
	while (1) {
		//OSSemPend(event, 0, &err);
		while (OSTCBCur->compTime > 0) //C ticks 
		{
			// do nothing
		}
		end = OSTimeGet(); // end time
		toDelay = 4 - (end - start);
		start = start + 4; // next start time
		OSTCBCur->compTime = 1; // reset the counter (c ticks for computation) 
		//OSSemPost(event);
		OSTimeDly(toDelay); // delay and wait (T-C) times
	}
}

static void Task2(void *p_arg)
{
	int start; //the start time 
	int end; //the end time 
	int toDelay;
	start = 0;
	OSTCBCur->compTime = 2;
	while (1) {
		while (OSTCBCur->compTime > 0) //C ticks 
		{
			// do nothing
		}
		end = OSTimeGet(); // end time
		toDelay = 5 - (end - start);
		start = start + 5; // next start time
		OSTCBCur->compTime = 2; // reset the counter (c ticks for computation) 
		OSTimeDly(toDelay); // delay and wait (T-C) times
	}
}

static void Task3(void *p_arg)
{
	int start; //the start time 
	int end; //the end time 
	int toDelay;
	start = 0;
	OSTCBCur->compTime = 3;
	while (1) {
		//OSSemPend(event, 0, &err);
		while (OSTCBCur->compTime > 0) //C ticks 
		{
			// do nothing
		}
		end = OSTimeGet(); // end time
		toDelay = 6 - (end - start);
		start = start + 6; // next start time
		OSTCBCur->compTime = 3; // reset the counter (c ticks for computation) 
		//OSSemPost(event);
		OSTimeDly(toDelay); // delay and wait (T-C) times
	}
}
