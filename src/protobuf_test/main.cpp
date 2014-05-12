///> ����.proto�ļ�,��protoc.exe���ɶ�Ӧ��.h��.cpp�ļ�,����:
///> protoc  -I=.\   --cpp_out=.\   sr.ProtoTest.proto

#include <string>
#include "sr.ProtoTest.pb.h"

int main(int argc, char **argv)
{
    sr::ProtoTest info1;
    info1.set_id(32);
    info1.set_name("siren", 20);
    info1.set_email("siren186@163.com", 50);

    ///> ���л���string
    std::string strBuf;
    info1.SerializeToString(&strBuf);

    ///> �����л�
    sr::ProtoTest info2;
    info2.ParseFromString(strBuf);

    return 0;
}