#include "NameCard.h"

NameCard * MakeNameCard(char * name, char * phone)
{
	if (strlen(name) > NAME_LEN) return NULL;
	if (strlen(phone) > PHONE_LEN) return NULL;

	NameCard *newCard = (NameCard*)malloc(sizeof(NameCard));
	strcpy(newCard->name, name);
	strcpy(newCard->phone, phone);
	return newCard;
}

void ShowNameCardInfo(NameCard * pcard)
{
	printf("Name : %s, Phone : %s \n", pcard->name, pcard->phone);
}

int NameCompare(NameCard * pcard, char * name)
{
	return strcmp(pcard->name, name);
}

void ChangePhoneNum(NameCard * pcard, char * phone)
{
	// 번호 길이가 저장할수있는 길이보다 길면 저장하지않음
	if (strlen(phone) > PHONE_LEN) return;
	strcpy(pcard->phone, phone);
}
