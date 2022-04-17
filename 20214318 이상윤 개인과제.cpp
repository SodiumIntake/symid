#define _CRT_SECURE_NO_WARNINGS
#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

SceneID scene,scene1,scene2,scene3,scene4,scene5,scene6,scene7,scene8;
ObjectID start,start2, end,end2, end3, bd1, bd2, num[8], poke, poke2,poke3, ball[3],hp[7],gauge,move, check;
SoundID enter, fight, ending;
TimerID timer1, timer2,timer3,timer4;

int x1 = 300, y1 = 200;
int x2 = 400, y2 = 500;
int x3 = 700, y3 = 100;
int x4 = 0, y4 = 366;
int dx = 1, dy = 1;
int ct ;


#define ANIMATION_TIME1		0.0001f
#define ANIMATION_TIME2		0.0001f


ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown, float num) {

	ObjectID object = createObject(image);
	if (shown == true) {
		locateObject(object, scene, x, y);
		showObject(object);
		scaleObject(object, num);
	}
	return object;
}

int shownhide(bool first) {
	if (first == true){
		for (int i = 0; i < 3; i++)
			hideObject(num[i]);
	}

	if (first == false) {
		for (int i = 0; i < 3; i++)
			showObject(num[i]);
	}
	return(0);
}



int count=0 ,count2 = 0;
int counter() {
	if (count == 1) {
		showMessage("문을 제대로 찾지 못했어.. 포켓몬 센터라도 다녀올까?");
		enterScene(scene3);
	}
	return(0);
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == bd1) {
		showMessage("문을 잘 고르면 관장을 만날 수 있을거야!");
		enterScene(scene1);
	}

	else if (object == bd2){
		enterScene(scene3);
		showMessage("엇?");
	}

	else if (object == start) {
		enterScene(scene4);
		showMessage("내 캐이시가 도망쳤어.. 캐이시를 잡아주면 체육관으로 보내줄게!!\n 작은녀석이라 찾기 힘들지도 몰라..");
		startTimer(timer1);
	}

	else if (object == end)
		endGame();

	else if ((object == num[0]) || (object == num[1])) {
		showMessage("3번문은 정답이 아니야 정말 이게 맞아?");
		shownhide(true);
	}
	else if (object == num[2]) {
		showMessage("1번문은 정답이 아니야 정말 이게 맞아?");
		shownhide(true);
	}
	else if ((object == num[3]) || (object == num[5])) {
		showMessage("틀렸어 정답이 아닌걸..");
		shownhide(false);
		count += 1;
		counter();
	}
	else if (object == num[4]) {
		showMessage("정답이야 들어가면 돼!");
		enterScene(scene5);
		showMessage("나는 간단한 퀴즈만 맞추면 통과시켜줄게~!\n아까 첫 번째 문 문제에서 선택을 바꾸는게 유리할까? 그냥 그대로 가는게 유리할까?\n 1. 바꾼다 2. 안바꾼다");

	}
	else if (object == end2) {
		enterScene(scene);
	}

	else if (object == poke) {
		dropObject(ball[0]);
		hideObject(ball[0]);
		showMessage("아쉽게 놓쳤어.. 엇 그리고 새로운 캐이시가 나타났어!");
		showObject(poke2);
		scaleObject(poke2, 0.4f);
		hideObject(poke);
		showObject(poke3);
		scaleObject(poke3, 0.4f);

		count2 += 1;
	}
	else if (object == poke3) {
		dropObject(ball[1]);
		hideObject(ball[1]);
		showMessage("이 캐이시가 아닌거같은데..");
		hideObject(poke3);
	}
	else if (object == poke2) {
		dropObject(ball[2]);
		hideObject(ball[2]);
		showMessage("오 고마워 내 캐이시를 찾아줬구나!!");
		enterScene(scene5);
		showMessage("나는 간단한 퀴즈만 맞추면 통과시켜줄게~!\n아까 첫 번째 문 문제에서 선택을 바꾸는게 유리할까? 그냥 그대로 가는게 유리할까?\n 1. 바꾼다 2. 안바꾼다");
	}
	else if (object == num[6]) {
		enterScene(scene6);
		stopSound(enter);
		fight = createSound("Sounds\\관장.mp3");
		playSound(fight, true);
		showMessage("여기까지 오다니 반가워!!\n 나는 연고시티 관장 멜리사야\n 나와의 배틀이 준비되면 스타트버튼을 눌러줘~");
	}
	else if (object == num[7]) {
		enterScene(scene3);
		showMessage("에잇 포켓몬센터나 다녀와야겠다..");
	}
	else if (object == start2) {
		enterScene(scene7);
		startTimer(timer2);
	}

	else if (object == check) {
		stopTimer(timer2);
		ct = 0;

		if ((0 <= x4) && (x4< 50)) {
			showMessage("공격이 빗나갔어..");
			startTimer(timer3);
		}
		else if ((50 <= x4) && (x4 < 100)) {
			showMessage("공격이 효과가 있는 것 같아!");
			setObjectImage(hp[0], "Images\\25%.png");
			ct += 1;
			startTimer(timer4);
		}
		else if ((100 <= x4) && (x4 < 150)) {
			showMessage("공격이 효과가 있는 것 같아!");
			setObjectImage(hp[0], "Images\\50%.png");
			ct += 1;
			startTimer(timer4);
		}
		else {
			showMessage("공격이 효과가 굉장해!");
			setObjectImage(hp[0], "Images\\0%.png");
			startTimer(timer4);
		}
	}
	else if (object == end3) {
		endGame();
	}

	for (int i = 0; i < 3; i++) {
		if (object == ball[i]) {
			pickObject(ball[i]);
		}
	}
}



int r1() {
	x1 += dx; y1 += dy;
	x2 -= dx; y2 += dy;
	x3 += dx; y3 -= dy;

	return(0);
}
int r2() {
	x1 -= dx; y1 -= dy;
	x2 += dx; y2 -= dy;
	x3 -= dx; y3 += dy;

	return(0);
}
int r3() {
	x1 += dx; y1 -= dy;
	x2 += dx; y2 += dy;
	x3 -= dx; y3 -= dy;

	return(0);
}
int r4() { 
	x1 -= dx; y1 += dy;
	x2 -= dx; y2 -= dy;
	x3 += dx; y3 += dy;

	return(0);
}


void timerCallback(TimerID timer) {
	if (timer == timer1) {
		srand(time(NULL));
		int a = rand() % 4;
		if (a == 0)
			r1();
		if (a == 1)
			r2();
		if (a == 2)
			r3();
		if (a == 3)
			r4();

		locateObject(poke, scene4, x1, y1);
		if (count2 == 1) {
			locateObject(poke2, scene4, x2, y2);
			locateObject(poke3, scene4, x3, y3);
		}

		setTimer(timer1, ANIMATION_TIME1);
		startTimer(timer1);
	}
	if (timer == timer2){
		x4 += dx;
		if (x4 == 200) {
			x4 = 0;
		}

		locateObject(move, scene7, x4, y4);

		setTimer(timer2, ANIMATION_TIME1);
		startTimer(timer2);
	}

	if (timer == timer3) {
		setObjectImage(hp[1], "Images\\die.png");
		enterScene(scene);
		stopSound(fight);
		playSound(enter, true);
		showMessage("생각보다 센 관장의 공격에 쓰러져버렸어..");
		setObjectImage(hp[1], "Images\\피통1.png");
		setObjectImage(hp[0], "Images\\피통2.png");
	}

	if (timer == timer4) {
		if (ct == 1) {
			setObjectImage(hp[1], "Images\\die.png");
			startTimer(timer3);
		}

		if (ct == 0) {
			enterScene(scene8);
			stopSound(fight);
			ending = createSound("Sounds\\ending.mp3");
			playSound(ending, false);
			showMessage("관장 공략 성공!");
		}
	}
}


int main() {
	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);

	timer1 = createTimer(ANIMATION_TIME1);
	timer2 = createTimer(ANIMATION_TIME1);
	timer3 = createTimer(4.0f);
	timer4 = createTimer(4.0f);

	scene8 = createScene("끝", "Images\\끝.png");
	end3 = createObject("Images\\end.png", scene8, 450, 50, true, 1.3);

	scene6 = createScene("진", "Images\\관장전.png");
	start2 = createObject("Images\\start.png", scene6, 500, 50, true, 1.3);
	
	scene7 = createScene("배틀", "Images\\배틀.png");
	hp[0] = createObject("Images\\피통2.png", scene7, 700, 400, true, 1);
	hp[1] = createObject("Images\\피통1.png", scene7, 0, 0, true, 1);

	gauge = createObject("Images\\게이지.png", scene7, 0, 400, true, 0.4);
	move = createObject("Images\\게이지이동.png", scene7, x4, y4, true, 0.08);
	check = createObject("Images\\check.png", scene7, 70, 250, true, 0.7);

	scene5 = createScene("준", "Images\\시트론.png");
	num[6] = createObject("Images\\1.png", scene5, 350, 0, true, 0.1);
	num[7] = createObject("Images\\2.png", scene5, 650, 0, true, 0.1);
	

	scene = createScene("연고시티", "Images\\연고시티원.png");
	ball[0] = createObject("Images\\몬스터볼.png", scene, 200, 50, true, 0.09);
	ball[1] = createObject("Images\\몬스터볼.png", scene, 300, 550, true, 0.09);
	ball[2] = createObject("Images\\몬스터볼.png", scene, 800, 300, true, 0.09);

	end = createObject("Images\\end.png", scene, 450, 50, true, 1.3);
	bd1 = createObject("Images\\체육관.png", scene, 740, 430, true, 1);
	bd2 = createObject("Images\\포켓몬센터.png", scene, 230, 430, true, 1);
	enter = createSound("Sounds\\연고시티.mp3");
	playSound(enter, true);

	scene1 = createScene("내부배경", "Images\\내부배경.png");
	num[3] = createObject("Images\\1.png", scene1, 120, 450, true, 0.15);
	num[4] = createObject("Images\\2.png", scene1, 550, 450, true, 0.15);
	num[5] = createObject("Images\\3.png", scene1, 980, 450, true, 0.15);
	num[0] = createObject("Images\\1.png", scene1, 120, 450, true, 0.15);
	num[1] = createObject("Images\\2.png", scene1, 550, 450, true, 0.15);
	num[2] = createObject("Images\\3.png", scene1, 980, 450, true, 0.15);
	
	scene3 = createScene("문 미션 실패", "Images\\센터내부.png");
	start = createObject("Images\\start.png", scene3, 450,50, true, 1.3);
	
	scene4 = createScene("포켓몬센터", "Images\\오박사.png");
	poke = createObject("Images\\ball.png", scene4, x1, y1, true, 0.04);
	poke2 = createObject("Images\\ball.png",scene4, x2, y2, false, 0.5);
	poke3= createObject("Images\\ball.png",scene4, x3, y3, false, 0.5);
	end2 = createObject("Images\\end.png", scene4, 450, 50, true, 1.3);
	startGame(scene);
	
}