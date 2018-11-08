//
// Created by ljf on 11/8/18.
//

#ifndef GAMESERVER_REGISTERBUSINESS_H
#define GAMESERVER_REGISTERBUSINESS_H

#include "IBusiness.h"
namespace Business
{
    class RegisterBusiness :implements IBusiness
    {
    public:
        RegisterBusiness(int id);
        int Get_ID() override;
        int Process(char *buf,void *ev) override;
    protected:

    private:
        //MSG ID
        int id;
    };
}



#endif //GAMESERVER_REGISTERBUSINESS_H
