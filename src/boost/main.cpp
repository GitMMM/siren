/**
 * ����
 * siren186@163.com
 * 2014-05-13
 * 
 * 
 * ����boost����(��Ȼbjam��ǿ��,��Ҳ������,�򵥾ͺ�)
 * 1. ����bootstrap.bat, ����bjam.exe
 * 2. ʹ��bjam.exe����������Ӧ��boost��.��:
 *  �÷�1:
 *      bjam toolset=msvc-10.0 install  ///> ȫ����װ(�汾VC10),�Ὣ���ɵ��ļ�,������C:\Boost.�ļ�������bin.v2��.
 *  �÷�2:
 *      bjam toolset=msvc-8.0 stage    ///> ȫ����װ(�汾VC8),������C����������Ӧ����,�ļ�����boost�µĵ�bin.v2�ļ�����
 *  �÷�3:
 *      bjam toolset=msvc-10.0 --with-regex stage       ///> ������regexp��,�����ⲻ����.ʡʱ��
 *  �÷�4:
 *      bjam toolset=msvc-10.0 --without-python stage   ///> ������python��
 *      
 *      
 *  �����ɵ���Ӧ���ļ�,������siren����Ŀ¼:\output\lib\��,�����������뱾����.
 */
#include <boost/thread.hpp> 
#include <iostream> 

void wait(int seconds) 
{ 
    boost::this_thread::sleep(boost::posix_time::seconds(seconds)); 
} 

void thread() 
{ 
    for (int i = 0; i < 5; ++i) 
    { 
        wait(1); 
        std::cout << i << std::endl; 
    } 
} 

int main(int argc, char **argv)
{
    boost::thread t(thread); 
    t.join(); 
    return 0;
}