#include <Windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class Thread {

protected:

	//�ڽĿ��Ը� �Ʒ��� �Լ��� ����

	virtual void threadMain() {}
	   
	static unsigned long __stdcall __threadMain(void *args) {

		Thread* self = (Thread*)args;

		self->threadMain();

		return 0;

	}

public:
	
	void run() {   //void run(Thread* const this)
		CreateThread(0, 0, __threadMain, (void*)this, 0, 0);
	}
};

class FileDownThread : public Thread {

public:
	int n;

	//threadMain�� �������̵��ϸ� �˴ϴ�.

	void threadMain() {
		for (int i = 0; i <= 10; i++) {
			//system("cls");
			
			cout << i * 10 << "% downloading" << endl;
			Sleep(700);
		}
	}
};

int main(void) {

	FileDownThread t;
	t.run();

	getchar();
	

	return 0;
}

