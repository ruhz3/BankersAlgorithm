#include <iostream>
#include <vector>
#include <string>
using namespace std;


int N;	// Process의 개수 
int M;	// Resource Type의 개수

int Max[200][200];
int Allocation[200][200];
int Need[200][200];
int Available[200];

bool Finish[200];
int Sequence[200];

// 사용자 정의 함수
void InputValues();
void BANKER();
void PrintChange(int);
void PrintInfo();

int main() {
	cout << "======================================================" << endl;
	cout << "=                  OS Assignment #3                  =" << endl;
	cout << "=               : Banker's Algorithm                 =" << endl;
	cout << "=                                 2016112650 류형주  =" << endl;
	cout << "======================================================" << endl;

	// Process들의 정보를 입력
	InputValues();

	// Sequence 입력
	cout << "\nProcess Sequence[] : ";
	for (int i = 0; i < N; i++) {
		cin >> Sequence[i];
	}

	// Banker's Algorithm 구현함수
	BANKER();

	int get;
	cout << "Type Anything -> Enter to Exit!" << endl;
	cin >> get;

	return 0; 
}

void InputValues() {
	cout << "<Input>" << endl;
	cout << "Number of Process : ";
	cin >> N;
	cout << "Number of Resource Type : ";
	cin >> M;

	cout << "\nAvailable[] Matrix : " << endl;
	cout << " ex) Available[j] = k : j번 리소스는 k개 Available" << endl;
	for (int j = 0; j < M; j++) {
		cin >> Available[j];
	}

	cout << "\nMax[][] Matrix : " << endl;
	cout << " ex) Max[i][j] = k : i번 프로세스는 j번 리소스를 최대 k개 요구" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Max[i][j];
		}
	}
	cout << "\nAllocation[][] Matrix : " << endl;
	cout << " ex) Allocation[i][j] = k : i번 프로세스는 j번 리소스가 현재 k개 할당됨" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Allocation[i][j];
		}
	}
	cout << "\nNeed[][] Matrix : Auto Input..." << endl;
	cout << " ex) Allocation[i][j] = k : i번 프로세스는 j번 리소스가 k개 필요함" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			Need[i][j] = Max[i][j] - Allocation[i][j];
			printf("%3d", Need[i][j]);
		}	puts("");
	}

	PrintInfo();
}

void BANKER() {
	int order = 0;

	while (true) {
		// 모든 프로세스가 Finish면 탈출
		bool exit = true;
		for (int i = 0; i < N; i++) {
			if (!Finish[i])
				exit = false;
		}
		if (exit) {
			cout << "SAFE : this sequence works!" << endl;
			return;
		}
		int idx = Sequence[order];
		cout << "\n\n" << endl;
		cout << "======================================================" << endl;
		cout << order + 1 << "번째 : Process"<< idx << endl;

		// Need값이 만족되도록 할당 가능한 지 검사
		bool canAlloc = true;
		for (int j = 0; j < M; j++) {
			if (Need[idx][j] > Available[j])
				canAlloc = false;
		}
		
		// 할당 가능하다면
		if (canAlloc) {
			// 1. Allocation
			PrintChange(idx);	// Need, Available 값 출력
			for (int j = 0; j < M; j++) {
				Available[j] -= Need[idx][j];
				Allocation[idx][j] += Need[idx][j];
				Need[idx][j] = 0;
			}
			cout << " ㅣ " << endl;
			cout << " ㅣ (Allocate!)" << endl;
			cout << " ㅣ " << endl;
			cout << " ▽ " << endl;
			PrintChange(idx);

			// 2. Release
			for (int j = 0; j < M; j++) {
				Available[j] += Allocation[idx][j];  
				Allocation[idx][j] = 0;
				Finish[idx] = true;
			}
			cout << " ㅣ " << endl;
			cout << " ㅣ (Release!)" << endl;
			cout << " ㅣ " << endl;
			cout << " ▽ " << endl;
			PrintChange(idx);
			cout << "======================================================" << endl;
		}
		// 할당이 안 된다면
		else {
			cout << "UNSAFE : this sequence doesn't work!" << endl;
			PrintInfo();
			return;
		}
		// 다음 인덱스 검사
		order++;
	}
}

void PrintChange(int process) {
	int idx = process;

	printf("Need      : ");
	for (int j = 0; j < M; j++) {
		printf("%3d", Need[idx][j]);
	}
	puts("");
	
	printf("Available : ");
	for (int j = 0; j < M; j++) {
		printf("%3d", Available[j]);
	}
	puts("");
}

void PrintInfo() {
	cout << "\n============================================================================================================" << endl;
	// 첫째 줄
	printf("%-6s%-30s%-30s%-30s\n", "", "Allocation", "MAX", "Available");

	// 둘째 줄
	printf("%6s", "");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < M; j++) {
			printf("R%-2d ", j);
		}
		for (int k = 0; k < 30 - 4 * M; k++) {
			printf(" ");
		}
	}
	puts("");
	// 셋째 줄 ~ (N+3)번째 줄
	for (int i = 0; i < N; i++) {
		printf(" P%-2d  ", i);
		for (int j = 0; j < M; j++) {
			printf("%-3d ", Allocation[i][j]);
		}
		for (int k = 0; k < 30 - 4 * M; k++) {
			printf(" ");
		}
		for (int j = 0; j < M; j++) {
			printf("%-3d ", Max[i][j]);
		}
		for (int k = 0; k < 30 - 4 * M; k++) {
			printf(" ");
		}
		if (i == 0) {
			for (int j = 0; j < M; j++) {
				printf("%-3d ", Available[j]);
			}
			for (int k = 0; k < 30 - 4 * M; k++) {
				printf(" ");
			}
		}
		puts("");
	}
	cout << "============================================================================================================\n" << endl;
}