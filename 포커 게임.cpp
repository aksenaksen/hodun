#include <stdio.h>
#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5

int num_in_rank[NUM_RANKS + 1];
int num_in_suit[NUM_SUITS];
char R[NUM_CARDS] = { '0' }, S[NUM_CARDS] = { '0' };

void read_cards(void);
void analyze_hand(void);

int main(void) {
	int retry;
	while (1) {
		printf("***************START*GAME***************\n");//start game
		read_cards();
		analyze_hand();
		printf("\n*****************THE**END*****************\n");
		printf("RETRY? (Do you want to exit this game, click -1): ");
		scanf(" %d", &retry);
		printf("\n\n");
		if (retry == -1)break;
	}
}

void init_data() { //������ ������ �ݺ� --> �Ź� �� �迭�� 0���� �ʱ�ȭ
	int rank, suit;

	for (rank = 0; rank < NUM_RANKS; rank++)
		num_in_rank[rank] = 0;
	for (suit = 0; suit < NUM_SUITS; suit++)
		num_in_suit[suit] = 0;
}

int overlap(char A,char B,int N) { //�ߺ� Ȯ�� �Լ�
	int check = 0;
	for (int i = 0; i < N; i++) {
		if (R[i] == A && S[i] == B) check = 1;//�ߺ��� rank�� �Ȱ��� suit�� �Ȱ��� ��
	}
	if (check == 1) return 1;//�ߺ��̶�� 1 ��ȯ
	else return 0;
}

void read_cards(void) { //ī�� �Է¹޴� �Լ�
	char ch, rank_ch, suit_ch;
	int rank, suit;

	init_data();

	int cards_read = 0;

	while (cards_read < NUM_CARDS) {
		int check = 0;
		printf("Enter a card(%d):", cards_read + 1);
		scanf(" %c", &rank_ch); R[cards_read] = rank_ch; //rank�� ��Ÿ���� �ϳ��� ���� �Է�
		switch (rank_ch) {
		case 'a': rank = 1; break;
		case '2': rank = 2; break;
		case '3': rank = 3; break;
		case '4': rank = 4; break;
		case '5': rank = 5; break;
		case '6': rank = 6; break;
		case '7': rank = 7; break;
		case '8': rank = 8; break;
		case '9': rank = 9; break;
		case 't': rank = 10; break;
		case 'j': rank = 11; break;
		case 'q': rank = 12; break;
		case 'k': rank = 13; break;
		default: printf("\nUNKNOWN_RANK(Retry)\n\n"); check = 1; break; //�߸��Է��ϸ� �ٽ�
		}
		scanf(" %c", &suit_ch); S[cards_read] = suit_ch;
		switch (suit_ch) {
		case 'c': suit = 0; break;
		case 'd': suit = 1; break;
		case 'h': suit = 2; break;
		case 's': suit = 3; break;
		default: printf("\nUNKNOWN_SUIT(Retry)\n\n"); check = 1; break; //�߸��Է��ϸ� �ٽ�
		}
		if (check == 0) { //�ߺ� �˻�
			if (overlap(rank_ch, suit_ch, cards_read) == 1) printf("\nDUPLICATE\n\n");
			else {
				num_in_rank[rank]++;
				num_in_suit[suit]++;
				cards_read++;
			}
		}
	}
}

int check_four_cards() {
	int check = 0;
	for (int rank = 1; rank < NUM_RANKS + 1; rank++) {
		if (num_in_rank[rank] == 4) check = 1; //��ī�� ����
	}
	if (check == 1) return 1;
	else return 0;
}

int check_flush() { //5�� ��� ������ suit
	int check = 0;
	for (int suit = 0; suit < NUM_RANKS; suit++) {
		if (num_in_suit[suit] == 5) check = 1; // flush ����
	}
	if (check == 1) return 1;
	else return 0;
}

int check_straight() {
	int check = 0;
	for (int rank = 1; rank < NUM_RANKS; rank++) {
		if (num_in_rank[rank] == 5) check = 1; //straigth ����
	}
	if (check == 1) return 1;
	else return 0;
}

int check_triple() {
	int check = 0;
	for (int rank = 1; rank < NUM_RANKS; rank++) {
		if (num_in_rank[rank] == 3) check =1; //triple ����
	}
	if (check == 1) return 1;
	else return 0;
}

int check_pair() {
	int count = 0;
	for (int rank = 1; rank < NUM_RANKS; rank++) {
		if (num_in_rank[rank] == 2) count++; //pair ����
	}
	if (count == 2) return 2;
	else if (count == 1) return 1;
	else return 0;
}

void analyze_hand(void) {// ������ �Լ����� �̿��Ͽ� ���� ���� ī�� �и� �ν��Ͽ� ����Ѵ�.
	printf("\n");
	if (check_straight() == 1 && check_flush() == 1) printf("Straight Flush!!\n"); //straight flush --> straight�̸鼭 flush
	else if (check_four_cards()==1) printf("Four Cards!!\n"); //four card
	else if (check_triple() == 1 && check_pair() == 1) printf("Full House!!\n"); //full house --> triple�̸鼭 pair
	else if (check_flush() == 1) printf("Flush!!\n"); //flush
	else if (check_straight() == 1) printf("Straight!!\n"); // straght
	else if (check_triple() == 1) printf("Triple!!\n"); //triple
	else if (check_pair() == 2)printf("Two Pairs!!\n"); // two pairs
	else if (check_pair() == 1) printf("Pair!!\n"); // pair
	else printf("High Card!!\n");
}