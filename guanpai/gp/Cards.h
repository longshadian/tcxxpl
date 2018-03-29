#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <list>
#include <functional>

/// 一张扑克牌用int32_t表示。只使用最低8位
/// 低8位描述, 高4位代表花色，低4位代表牌值
/// 数值	   0        1       2       3	
/// 花色	 方块     梅花      红桃  	黑桃	

/// 数值	    0       1   2   3   4   5   6   7   8   9   10  11  12  13  14      15
/// 牌值	    空牌    3   4   5   6   7   8   9   10  J   Q   K   A   2   小王	    大王
/// 小王和大王高4位设为0

namespace gp_alg {

/// 花色
enum Color
{
    Diamond  = 0,       // 方块
    Club     = 1,       // 梅花
    Heart    = 2,       // 红桃
    Spade    = 3,       // 黑桃
    Color_Count = 4,
};

/// 牌值
enum Value
{
    Card_Null   = 0,
    Card_3      = 1,
    Card_4      = 2,
    Card_5      = 3,
    Card_6      = 4,
    Card_7      = 5,
    Card_8      = 6,
    Card_9      = 7,
    Card_10     = 8,
    Card_J      = 9,
    Card_Q      = 10,
    Card_K      = 11,
    Card_A      = 12,
    Card_2      = 13,
    Card_B      = 14,   // black joker
    Card_R      = 15,   // red joker
    Card_Count
};

/// 牌型
enum class Type 
{
    Type_Null          = 0x00,	//未定义
    Type_Signle        = 0x01,	//单牌
    Type_Single_Ser    = 0x02,	//顺子
    Type_Double        = 0x03,	//对子
    Type_Double_Ser    = 0x04,	//连对
    Type_Triple        = 0x05,	//三个
    Type_Triple_Ser    = 0x06,	//三顺(飞机)
    Type_41            = 0x07,	//4带1单
    Type_31            = 0x08,	//3带1单 AAA + ?
    Type_Bomb          = 0x09,	//炸弹
    Type_Mask          = 0x10,	//牌型掩码
};

/// 卡牌数量
enum { QUANTITY = 54 };

using Card = int32_t;

using CardPosition = std::list<Card>;    //牌所在的位置, size()最大为4

struct CardType
{
    CardType();
    CardType(Type type, Value value, int32_t type_len);

    bool operator<(const CardType& rhs) const;
    bool operator==(const CardType& rhs) const;
    bool operator!=(const CardType& rhs) const;

     //牌型
    Type        m_type;

    //牌值:取得是规则化后主牌的最小值，例如:
    //JJJ QQQ KKK 33 44 55,这手牌的牌值是J
    // A K J Q 10 7 8 9,规则化后AKQJ10987 这牌值是7
    Value       m_value;

    //牌型长度(如果该牌型有长度)
    int32_t     m_type_len;
};

inline
int32_t makeColor(Card card, Color color)
{
    return (((card) & 0x0F) | (color) << 4);
}

inline
int32_t makeValue(int32_t card, Value value)
{
    return (((card) & 0xF0) | (value));
}

inline 
Color getCardColor(int32_t card) 
{
    return static_cast<Color>(((card)&0x30) >> 4);
}

inline 
Value getCardValue(int32_t card)
{
    return static_cast<Value>((card) & 0x0F);
}

/*
#define setCardColor(card, color)   (((card) & 0x0F) | (color) << 4)
#define setCardValue(card, value)	(((card) & 0xF0) | (value))
#define	getCardColor(card)			(((card)&0x30) >> 4)
#define	getCardValue(card)			((card) & 0x0F)
#define setCard(color,value)		(((color)<<4) | ((value)&0x0F))
*/

/** 
 * 初始化牌型
 */
void initCard(std::vector<Card>& card);
std::vector<Card> initCard();

/**
 * 检查选中牌能否压过目标牌
 * 注意：src hand无需牌型化,
 *      如果src hand不是合法的牌型，返回false
 * Params   src,src_len 目标牌
 *          hand,hand_len 选中的牌
 * Returns  true:能压过    false:不能压过
 */
bool check(const Card* src,  int32_t src_len,
           const Card* hand, int32_t hand_len);

/**
 * 检查选中牌能否压过目标牌,如果src为空或src_len==0，只要检查选中牌是否合法
 * 注意：src hand无需牌型化
 * Params   src,src_len 目标牌
 *          selected,selected_len 选中的牌
 *          out:打出去的牌而且是规则化的。
 *          注意:out缓冲区不能小于selected_len
 * Returns  true:能压过    false:不能压过
 */
bool playCard(const Card* src,       int32_t src_len,
              const Card* selected,  int32_t selected_len,
              Card* out);

/**
 * 自动选择选中可以压过目标的牌。类似提示功能
 * Params   src,src_len:目标牌
 *          hand,hand_len:手中的牌
 *          out:值不等于0就是选中的能压过目标牌的牌。
 *          注意：out的长度不能少于hand_len,选中的牌是未规则化。
 * Returns  true:能压过    false:不能压过
 */
bool autoSelect(const Card* src,     int32_t src_len,
                const Card* hand,    int32_t hand_len,
                Card* out); 

//去除空牌
std::vector<Card> removeCardNull(const Card* src, int32_t len);
std::vector<Card> removeCardNull(const std::vector<Card>& src);

/**
* 判断出牌类型，输出规则化牌型
* Params   src,src_len:需要判断的牌
*          out:输出规则化牌型
* Returns  返回牌型和牌型长度(如果该牌型有牌型长度)
*/
CardType parseCardType(const Card* src, int32_t len, std::vector<Card>* out);
CardType parseCardType(const Card* src, int32_t len);
CardType parseCardType(std::vector<Card>* src);


//比较牌值大小和花色大小，默认降序
class PreGreaterSort : public std::binary_function<Card, Card, bool>
{
public:
    bool operator()(Card x, Card y) const
    {
        if (x == y)
            return false;
        Value x_val = getCardValue(x);
        Value y_val = getCardValue(y);
        if (y_val < x_val)
            return true;
        if (x_val < y_val)
            return false;

        //牌值相同按花色排序
        Color x_color = getCardColor(x);
        Color y_color = getCardColor(y);
        if (y_color < x_color)
            return true;
        if (x_color < y_color)
            return false;
        return true;
    }
};

class PreCardValue : public std::unary_function<Card, bool>
{
    int32_t val;
public:
    PreCardValue(int32_t v) : val(v) {}
    bool operator()(Card x) const
    {
        return val == getCardValue(x);
    }
};

/************************************************************************
 * 工具函数                                                                 
 ************************************************************************/
namespace utility {

struct CardNumString
{
    int32_t     m_num;
    std::string m_string;
};

} // utility


/************************************************************************
 * 内部实现
 ************************************************************************/
namespace detail {

struct Slot
{
    Value   m_value;
    std::array<uint8_t, 4> m_num;   // 4种花色，每种有几张牌
    uint8_t m_total_num;            // 不管花色，总共有几张
};

struct SlotClassify
{
    SlotClassify();
    std::array<Slot, 15> m_slots;               // 总共15种牌

    // 按照长度倒序排
    void sortByLengthDesc();
    std::vector<Slot>    m_sort_result;         // 牌最多的排前面
    int32_t              m_total_num_length;    // 牌长度相同的有几张
};

void sortCard(std::vector<Card>* src);

//int32_t getSameValueSeq(const Card* src, int32_t len, SameSeq* same_seq, bool need_sort);

bool createSlotClassify(const Card* src, int32_t len, SlotClassify* classify);

// 规格化牌
void normalizeTypeList(const SlotClassify& classify, std::vector<Card>* out);

/// 判断是否顺子
bool isSeries(const Card* src, int32_t len);

int32_t isSeries(const SlotClassify& classify, int32_t cnt);

int32_t compareCardType(const CardType& type1, const CardType& type2);

} // detail

} // gp_alg 
