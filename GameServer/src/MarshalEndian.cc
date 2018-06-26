/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：MarshalEndian.c
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年06月22日 17:58(Friday) 
 *   描    述：
 *
 ================================================================*/
#include <Interface.h>
#include "MarshalEndian.h"
#include "BaseMessage.h"
#include "string"
#include <fstream>
// 消息解析器  

void MarshalEndian::Initialize()
{
    //_LBuff = new list<char>(2);
    list<char> _LBuff(2);
    //utf8 = new UTF8Encoding();
}

void MarshalEndian:: Dispose()
{
	MarshalEndian:: Dispose(true);
    //GC.SuppressFinalize(this);
}

void MarshalEndian:: Dispose(bool flag1)
{
    if (flag1)
    {
       	// IDisposable disposable2 = this.utf8 as IDisposable;
       	// if (disposable2 != null) { disposable2.Dispose(); }
       	// IDisposable disposable = this._LBuff as IDisposable;
       	// if (disposable != null) { disposable.Dispose(); }
       	_LBuff.clear();
    }
}

//char* MarshalEndian:: Encode(IBaseMessage msg)
int MarshalEndian:: Encode(BaseMessage* msg,char *buf)
{
	char *msgBuffer = msg->GetByte();
	ofstream bw(buf, ios::binary);

	//#pragma region 封装包头  
    bw.write((char *)&t1,sizeof(t1));
    bw.write((char *)&t2,sizeof(t2));
	//#pragma endregion

	int len = 0;
	//#region 包协议  
    if (msg != NULL)
    {
    	len = sizeof(msgBuffer) + 4;
        bw.write((char *)&len,sizeof(len));
        bw.write((char *)&msg->MsgID,sizeof(msg->MsgID));
        bw.write(msgBuffer,sizeof(msgBuffer));
    }
    else
    {
    	bw.write((char *)&len,sizeof(len));
    }
	//#endregion

    return 0;
}

int MarshalEndian:: Decode(char *buff, int len,list<BaseMessage> ls)
{
    //拷贝本次的有效字节  
    char _b[len];
    strcpy(_b,buff);
    buff = _b;
    if (_LBuff.size() > 0)
    {
        //拷贝之前遗留的字节  
        _LBuff.AddRange(_b);
        buff = this._LBuff.ToArray();
        this._LBuff.Clear();
    }

    List<IBaseMessage> list = new List<IBaseMessage>();
    using (MemoryStream ms = new MemoryStream(buff))
    {
        using (BinaryReader buffers = new BinaryReader(ms, this.utf8))
        {
            try
            {
                byte[] _buff;

                while (true)
                {
#region 包头读取  
                    //循环读取包头             
                    //判断本次解析的字节是否满足常量字节数   
                    if ((buffers.BaseStream.Length - buffers.BaseStream.Position) < ConstLenght)
                    {
                        _buff = buffers.ReadBytes((int)(buffers.BaseStream.Length - buffers.BaseStream.Position));
                        this._LBuff.AddRange(_buff);
                        return list;
                    }
                    Int16 tt1 = buffers.ReadInt16();
                    Int16 tt2 = buffers.ReadInt16();
                    if (!(tt1 == t1 && tt2 == t2))
                    {
                        long ttttt = buffers.BaseStream.Seek(-3, SeekOrigin.Current);
                        continue;
                    }
#endregion

#region 包协议  
                    int offset = buffers.ReadInt32();
#endregion

#region 包解析  
                    //剩余字节数大于本次需要读取的字节数  
                    if (offset <= (buffers.BaseStream.Length - buffers.BaseStream.Position))
                    {
                        int msgID = buffers.ReadInt32();
                        _buff = buffers.ReadBytes(offset - 4);

                        IBaseMessage msg = ReceiverHelper.PopMessage();
                        msg.WriteIn(msgID, _buff, 0, _buff.Length);
                        list.Add(msg);
                        if ((buffers.BaseStream.Length - buffers.BaseStream.Position) > 0)
                        {
                            continue;
                        }
                    }
                    else
                    {
                        //剩余字节数刚好小于本次读取的字节数 存起来，等待接受剩余字节数一起解析  
                        _buff = buffers.ReadBytes((int)(buffers.BaseStream.Length - buffers.BaseStream.Position + ConstLenght));
                        this._LBuff.AddRange(_buff);
                    }
#endregion

                    break;
                }
            }
            catch (Exception ex)
            {
                Debug.LogErrorFormat("MarshalEndian Decode error: {0}", ex);
            }

        }
    }
    return list;
}


}
