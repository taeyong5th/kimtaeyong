#ifndef __SLOT_H__
#define __SLOT_H__

#include "Person.h"

typedef int		Key;	// 키 값이 되는 주민번호
typedef Person* Value;	// Person 구조체 변수의 값

//데이터가 저장된적이 없는지, 현재 비워진 상태인지, 유효한 데이터가 저장되어있는지.
enum SlotStatus { EMPTY, DELETED, INUSE };

typedef struct _slot
{
	Key				key;
	Value			val;
	enum SlotStatus status; // 슬롯의 상태를 나타낸다.
} Slot;

#endif
