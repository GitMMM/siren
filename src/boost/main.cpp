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
 *  �÷�5:
 *      bjam toolset=msvc-10.0 --with-regex stage debug release threading=multi threading=single link=shared link=static runtime-link=shared runtime-link=static
 *      
 *      
 *  �����ɵ���Ӧ���ļ�,������siren����Ŀ¼:\output\lib\��,�����������뱾����.
 */

#include <iostream> 
#include "gtest/gtest.h"
#include <boost/thread.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>

void thread() 
{ 
    for (int i = 0; i < 5; ++i) 
    { 
        boost::this_thread::sleep(boost::posix_time::seconds(1));
        std::cout << i << std::endl; 
    } 
} 

int main(int argc, char **argv)
{ 
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Boost, Thread)
{
    boost::thread t(thread); 
    t.join();
}

TEST(Boost, Log)
{
    boost::log::add_file_log("c:\\siren_boost.log");

    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info); ///> ����info�����¼���
    BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(info) << "An informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
    BOOST_LOG_TRIVIAL(error) << "An error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
}
