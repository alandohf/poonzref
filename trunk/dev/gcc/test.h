/*
 * =====================================================================================
 *
 *       Filename:  test.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/09/2010 09:36:17 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
typedef struct {
	int m_num;
	int *m_ind;
	int m_cnt;
}
ST_MIN;
 
 
	struct Flags
    {
      unsigned int Online  :1;   
      unsigned int Mounted :1;
//The :1 tells the compiler that only 1 byte is required for Online and Mounted. There are a few points to note about this though. 
    };
