﻿/*
* breeze License
* Copyright (C) 2015 - 2016 YaweiZhang <yawei.zhang@foxmail.com>.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/


#ifndef _ENTITY_H_
#define _ENTITY_H_


#include <common.h>
#include <DictCommon.h>
#include <DictScene.h>

#include <ProtoCommon.h>
#include <ProtoClient.h>
#include <ProtoSceneCommon.h>
#include <ProtoSceneServer.h>
#include <ProtoSceneClient.h>
#include <rvo2/RVO.h>


inline EPosition operator + (const EPosition & self, const EPosition & org) { return EPosition(self.x + org.x, self.y + org.y); }
inline EPosition operator - (const EPosition & self, const EPosition & org) { return EPosition(self.x - org.x, self.y - org.y); }
inline EPosition operator * (const EPosition & self, const EPosition & org) { return EPosition(self.x * org.x, self.y * org.y); }
inline EPosition operator / (const EPosition & self, const EPosition & org) { return EPosition(self.x / org.x, self.y / org.y); }

inline EPosition operator + (const EPosition & self, double val) { return EPosition(self.x + val, self.y + val); }
inline EPosition operator - (const EPosition & self, double val) { return EPosition(self.x - val, self.y - val); }
inline EPosition operator * (const EPosition & self, double val) { return EPosition(self.x * val, self.y * val); }
inline EPosition operator / (const EPosition & self, double val) { return EPosition(self.x / val, self.y * val); }

inline double getRadian(const EPosition & vt1, const EPosition & vt2) { return getRadian(vt1.x, vt1.y, vt2.x, vt2.y); }


inline EPosition normalize(const EPosition & dst) { if (std::abs(dst.x) > std::abs(dst.y)) { return EPosition(dst.x / dst.x, dst.y / dst.x); }return EPosition(dst.x / dst.y, dst.y / dst.y); }

inline double getDistance(const EPosition& pos1, const EPosition & pos2) { return getDistance(pos1.x, pos1.y, pos2.x, pos2.y); }

inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const RVO::Vector2 & v) { stm << "[" << v.x() << "," << v.y() << "]"; return stm; }
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const std::tuple<double, double> & v) { stm << "[" << std::get<0>(v) << "," << std::get<1>(v) << "]"; return stm; }
inline RVO::Vector2 toRVOVector2(const EPosition & pos) { return RVO::Vector2(pos.x, pos.y); }
inline std::tuple<double, double> toTuple(const EPosition & pos) { return std::make_tuple(pos.x, pos.y); }
inline EPosition toEPosition(const RVO::Vector2 & pos) { return EPosition(pos.x(), pos.y()); }
inline EPosition toEPosition(const std::tuple<double, double> & pos) { return EPosition(std::get<0>(pos), std::get<1>(pos)); }
inline DictProp operator + (const DictProp & ep1, const DictProp & ep2);
inline DictProp operator * (const DictProp & ep1, const DictProp & ep2);
inline DictProp operator * (const DictProp & ep, double df);


using DictID = unsigned long long;
const DictID InvalidDictID = -1;



using EntitySkillInfoPtr = std::shared_ptr<EntitySkillInfo>;

using EntityBuffInfoPtr = std::shared_ptr<EntityBuffInfo>;

struct EntitySkillSystem
{
    std::map<DictID, EntitySkillInfoPtr> activeSkills;
    std::map<DictID, EntityBuffInfoPtr> activeBuffs;
    std::set<DictID> dictBootSkills; 
    bool autoAttack = false;
};


struct EntityControl //EntityControl  
{
    unsigned long long eid = InvalidEntityID;


    //server
    unsigned long long agentNo = RVO::RVO_ERROR; //agentNo.   
    double stateChageTime = 0.0;
    EPosition spawnpoint; //出生点 
    double blockMoveCount = 0; //移动被阻次数
};






class Entity
{
public:
    Entity();
    ~Entity();
    double getSpeed();
    double getSuckBlood();
    double getAttack();
    EntityFullData getFullData();
    DictProp _props;
    EntityState  _state;
    EntityMove  _move;
    EntityReport _report;

    EntitySkillSystem _skillSys;
    EntityControl _control;
    SessionID _clientSessionID = InvalidSessionID;
    bool _isInfoDirty = false;
    bool _isMoveDirty = false;

};

using EntityPtr = std::shared_ptr<Entity>;
































inline DictProp operator + (const DictProp & ep1, const DictProp & ep2)
{
    DictProp ret;
    ret.hp = ep1.hp + ep2.hp;
    ret.attack = ep1.attack + ep2.attack;
    ret.moveSpeed = ep1.moveSpeed + ep2.moveSpeed;
    ret.attackQuick = ep1.attackQuick + ep2.attackQuick;
    return ret;
}

inline DictProp operator * (const DictProp & ep1, const DictProp & ep2)
{
    DictProp ret;
    ret.hp = ep1.hp * ep2.hp;
    ret.attack = ep1.attack * ep2.attack;
    ret.moveSpeed = ep1.moveSpeed * ep2.moveSpeed;
    ret.attackQuick = ep1.attackQuick * ep2.attackQuick;
    return ret;
}

inline DictProp operator * (const DictProp & ep, double df)
{
    DictProp ret;
    ret.hp = ep.hp * df;
    ret.attack = ep.attack * df;
    ret.moveSpeed = ep.moveSpeed * df;
    ret.attackQuick = ep.attackQuick * df;
    return ret;
}



#endif
