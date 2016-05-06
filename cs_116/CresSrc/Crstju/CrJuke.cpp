
int MusicFlag[100],MusicTable[100];

char *JukeComment[] = 
{
//---1
"クレスの曲の中でも、\
この”ミファーラー”のメロディがまず思い浮かび、\
この曲から作り始めました。\r\n\
メインとなるメロディーは、他の曲の中でも使われてます。\r\n\
実は・・・この曲はリミックス版だったりします。\
",

//---2
"私としては非常～に珍しく、題名から考えた曲です。\
竜の息のように力強く・・・かどうかはわかりませんが、\
元々、クレスでの使い道をどうしようか悩んでいた曲です。\r\n\
試しにオープニングにのせてみたら、けっこう合ったりして、そのまんま至ります。\r\n\
そして、オープニングだけではもったいないので、エターナル戦でも使うこととなりました。",

//---3
"夢の中にいるような、ぼんやりとした感じで作りました。\
ルナンの夢の中、そして幻惑の森の同じ場所でかかります。\r\n\
景色だけでは同じ場所と忘れてしまっても、曲で記憶を結びつけることにより、\
思い出すことができます。",

//---4
"唯一のフィールド曲。\r\n\
今回、フィールド曲は１つでいくことは、\
この曲ができた時点で決まりました。だっていい曲なんだもん。\r\n\
その気に入りようは、エンディングからもわかりますよね。",

//---5
"綾波ＦＣさんから、”シックなバトル曲を”との要望で作った曲です。\r\n\
普通のバトル曲だし、短くてシンプルです。\r\n\
あんまりゲームの戦闘の曲っぽくないのを目指してみたんですが・・・\
ちょっと中途半端だったかも。\r\n\
メロディは、本来サックスだけなんですが、ＧＭ／ＧＳ版では目立たないため、\
ストリングスを重ねてます。",

//---6
"とってもリアルなタイトル。（笑）\
私の通学路であり、一番よく通る道が国道１３４号線。\
海沿いを走り抜ける爽快感がこの曲です。\r\n\
もちろん、ファンファーレと合わせてイメージして作りました。\
とはいうものの、砂がまったり潮をかぶったり、そんな日もあるのです。",

//---7
"某Ｆ戦記2000の旅の後に作った曲です。\
とても広い、ずっと続く道を走っていました。\r\n\
町というと静かな落ち着く曲ですが、\
上のような作成動機から、こんな曲に仕上がってます。",

//---8
"なぜ”さかば”ではなく”さかさかば”なのか？\
　ただ単に語感がいい、という理由からです。\r\n\
発音したときの響きで、曲名を決めてしまうこともしばしば・・・",

//---9
"聞いての通りいいかげんな曲です。\
森とか洞窟とかで流れるので、こんなもんでいいかと。",

//---10
"泣く子もさらに泣き出す、中途半端な盗賊団、シューティングスターのテーマです。\
三等星なんて、肉眼で確認できるかどうか、ぎりぎりの明るさ。\
そんな明るさにしか光らず、一瞬で燃え尽きてしまう彼ら。嗚呼。",

//---11
"大道芸人（自称）のテーマ曲。演歌っぽく作ってみました。\r\n\
とは言うものの、私は演歌をほとんど知らないので、\
迫力にいまひとつ欠けてしまいました。\r\n\
実は・・・歌詞がちゃんとあるんです。\r\n\
前奏にもなってる一番盛り上がる部分は\
、”人生ライゼル　一陣の風が吹く”と唄います。唄いましょう。\r\n\
その後の伴奏だけの部分は、もちろん語りが入ります。ひゅるりら～。",

//---12
"微妙に主人公の名前ともかけてる曲。\r\n\
もともとは、車で道の丁度行く先に月があったことがはじまりです。\r\n\
この曲も、一般的なゲームの戦闘曲とは雰囲気を変えようとしました。\
同じ伴奏で、どれだけ違うメロディーが出せるか、\
そういったことも試してみました。",

//---13
"全滅の曲。でも明るいです。\r\n\
全滅したら暗い曲が流れて、ゲームオーバー、ではなくて、\
”お疲れさま”ということで、こういう曲調にしました。\r\n\
戦いの唄がベースになってることに気づいたかな？",

//---14
"最初、この曲はありませんでしたが、\
following the windがどうにも村には元気すぎて作ったものです。\
",

//---15
"タイトルとゲーム中で使われる場面には関係がないです。(^^;\r\n\
長い夢の目覚めは、きっとこんな感じなんでしょう。",

//---16
"幸せそうじゃない人達のテーマ。\r\n\
次のThe Eternalとメロディは一緒ですが、\
こっちの方があとから作りました。\
やる気のなさと、かったるさがじんわりと伝わってくるような曲です。\
でも、私はお気に入り。",

//---17
"エターナルのテーマ。でもあんまりかかる機会がなくてかわいそうでした。（笑）\r\n\
曲自体も、それほど目立つものではなく地味です。",

//---18
"ピンチっぽい時に流れる曲です。\r\n\
勢いだけで作ったら、へたっぴなバンドのような感じになってしまいましたが、\
これはこれで良しとしましょう。\r\n\
これなんては語感重視のタイトルですね。",

//---19
"迷ってるとき、困ってるとき、そしてちょっといい感じのとき、\
そんなときにこの曲が流れてきます。\r\n\
聞いての通り、Endless Wayが原曲になってます。",

//---20
"珍しくもストリングスオンリーの曲。\
幻惑の森を強調するために、ここだけの使用曲になってます。",

//---21
"クレイシヴのテーマ。\r\n\
不気味な、でも悲しい雰囲気を漂わす・・・そういった感じで作りました。\r\n\
でも、この曲が盛り上がる前に、だいたいのイベントは終わっちゃうんだな。\
これが。",

//---22
"学校について、ふと向こうの方を見たら、\
一点からもくもくと雲が沸き上がってました。\
そこから作ったのがこの曲です。\r\n\
ひたすら、同じ音を鳴らし続けてます。",

//---23
"”Sunday Sunday”と読みます。文字コードに指数表示がなかったので、\
こんな書き方になってしまいました。\
私がBASICで育ったことが一発でわかりますね。（笑）\r\n\
まぁ、pow(Sunday,2);なんて書いたら不気味なことこの上ないし・・・\r\n\
３連符系の軽快な曲です。町の中では一番のお気に入りです。",

//---24
"一度聞いたら、二度と頭から離れないであろう曲。\
最高のインパクトを誇ります。\r\n\
もともとはクレスで使うつもりはなかったんですが、\
あまりの個性的な音に誘惑され、マーチアレンジ後、\
不気味さを増してクレスで使うこととなりました。",

//---25
"”一陣の風”リコーダーバージョン。\r\n\
あの笑撃的なおじさんの衝撃的な過去の話で流れる曲です。\r\n\
ＦＦ９を遊んだあとに作ったのは内緒の話。（笑）",

//---26
"指輪探しでも使われますが、\
温泉シーンで使うことを目的に作りました。\r\n\
Endless Wayが原曲となってます。",

//---27
"緑豊かな村、アルシアの音楽です。\r\n\
いつものんびりしてて、自分の気持ちものんびりしてくる・・・\
そんな村ですが、\
アルシアのモデルって、私の大学なんです・・・",

//---28
"Endless Wayのピアノバージョン。\
ふと作ってみたら、これまたいい感じに。\
気に入ってしまったのでそのまんま使うこととなりました。",

//---29
"グラウンドシップの曲です。\r\n\
ＦＦ９を遊び、飛空挺の音楽に非常～に感激して、\
それよりももっといいのを作ろうという意気込みで出来上がった曲です。\r\n\
爽快に走り抜けるのではなくて、のんびりと飛ぶような、そんな感じです。\r\n\
私の中では１，２を争うほどお気に入りです。",

//---30
"ルナンが”運命を壊す”と言ってましたが、先に曲の方があり、\
それに合わせて会話を作りました。\r\n\
バトル曲って、使う場面で構成を変えます。\
”戦いの唄”は通常の戦闘で流れる曲なので、\
最初が一番インパクトがあるように、\
こういったイベントで続けて流れる曲は、曲全体でひとまとまりになるようにします。\r\n\
この曲、実は、カラオケに行ったら流れてそうな曲・・・\
をイメージして作ったんです。",

//---31
"”時の障壁”のアレンジバージョンです。\
あっちは勢いのある曲ですが、こちらの方はゆっくりと寂しい感じにしました。",

//---32
"この曲はかなり古いです。\
クレスのおおまかな話しか決まってない頃に作りました。\r\n\
時の障壁とは、\
長い時間が作ってしまう人と人との間にある見えない壁のこと。",

//---33
"ダンジョン用として作った曲です。\r\n\
どこで使うとまでは考えていませんでしたが、\
この冷たい感じから、忘れられた遺跡で使うことなりました。\r\n\
タイトルが妙に合ってるのは、使う場面に合わせて変更したから。",

//---34
"ちょっと可哀想なイベントで流れます。\
オルゴールの一番最後の曲になる人が多いんじゃないかな。\r\n\
”さかさかば”が原曲です。",

//---35
"降神祭で一曲作る、というのは考えてましたが、\
最初はジャンジャンと、オーケストラっぽいのでいくつもりでした。\r\n\
でもそれだとべたべたなので、ちょっと趣向を変えて、\
少し場違いかと思うくらいの曲にしてみました。\
シルバーリング完成後からずっと流れるも、\
バックミュージック的なものを狙ってみたからです。\r\n\
”Fated Force＝宿命の力”とは、知っての通り、\
ルナンのことです。",

//---36
"ずっとずっと昔に滅んだ伝説の都。その広大な都にはもう誰もいない・・・\
そんな雰囲気を出すようにしました。”滅び”がテーマです。\r\n\
無駄な音は出来るだけ避けて音の透明感を出すように、\
無機質なベースで空白感を出してます。たぶん。\r\n\
タイトルの彗星雨は、曲と、この言葉の持つ雰囲気から決めました。\
彗星って昔から”不吉な”現象の前触れとして恐れられたり、\
”伝染病を撒く”とか、”滅び”のイメージを私は持っていました。",

//---37
"最終決戦の曲です。\r\n\
どういった曲がいいか・・・かなり悩みました。\
音楽次第で、盛り上がりも盛り下がりもしちゃいますよね。\r\n\
二人がどちらを望むか、行き先はまるで逆です。\
それを決めるための曲が、これです。\r\n\
変身と曲の変わり目が一緒なのは、無理矢理、曲にメッセージを合わせたから。（笑）",

//---38
"永遠に目覚めぬ者、それが目覚めるとき、何が起きるのか・・・\r\n\
これはイベントの長さを考え、短めに作りました。",

//---39
"本当は、常に時の流れの中にいるんです。\
でもそれを感じられるのが、\
こうやって一人だけになったときなのかもしれません。\r\n\
",

//---40
"この場面、悲しいはずなんだけど、音楽は明るいです。\
無理に悲しい音楽を流して雰囲気を悪くするよりも、\
こういう曲にのせて、明るくエンディングを見てほしいです。\r\n\
世界にとってはかけらのようなものでも、誰かにとっては、\
それがとても大切なものだったりします。\r\n\
少し昔のことを思い出して、自然と歌が流れてきそうな、\
そんな曲を目指しました。",

//---41
"Endless Wayが原曲となってます。\
向こうが広く寂しい感じを漂わしますが、\
こちらは温かく、やすらぐように、\
できるだけシンプルに作りました。\
メロディもすぐに覚えてもらえるかと思います。\r\n\
曲を聞き終わったときに、心がほかほかとするような、\
そんなことを感じ取ってくれればうれしいです。\r\n\
Cresteajuのゲームはこれで終わりですが、物語はまだまだ続くはずです。",
};

int JukeCheck(void)
{
	int a;

	FILE *fp = fopen("cresjuke.exe","rb");
	if(fp == NULL)
		return 0;

	struct _finddata_t fd;
	_findfirst("cresjuke.exe",&fd);

	EIMEMORY hmem = eiAllocMemory(fd.size + 10000);
	if(hmem == NULL){
		fclose(fp);
		return 0;
	}

	ei_u8 *pdata = (ei_u8 *)eiLockMemory(hmem);

	fread(pdata,1,fd.size,fp);

	fclose(fp);


	//---チェック
	for(a = 0;a < (int)fd.size;a ++){
		if(pdata[a] == 'c'){
			if(strcmp((char *)(pdata + a),"cres_juke__") == 0){
				break;
			}
		}
	}

	eiFreeMemory(hmem);

	if(a == (int)fd.size)
		return 0;

	return 1;
}

eiCell JukeCell[8],JukeLogo[10];

int Juke(void)
{
	int a,b,check,item = 0;
	char s[100];
	int NowHour,NowMinute;
	char *file_name[] = {
		"Asgray.acf","Rarfia.acf","Crasive.acf","Follne.acf",
		"Dizza.acf","Lunarn.acf","Lizel.acf",
		"Xavier.acf","Yumi.acf","Cindy.acf","Edo.acf",
		"uni.acf","Tozoku1.acf","Tozoku2.acf","Nack.acf"
	};

	if(JukeCheck() == 0){
		return 0;
	}

	_tzset();
	_strtime(s);
	s[2] = 0;
	s[5] = 0;
	NowHour = atoi(&s[0]);
	NowMinute = atoi(&s[3]);

	//--------------------------------------
	int charat = NowHour / 2;
	if(((NowHour == 7 || NowHour == 19) && NowMinute == 9)){
		charat = 14;
	}
	sprintf(s,CR_DATADIR2"%s",file_name[charat]);
	eiCellReadPattern(JukeCell,
		s,CR_DATAFILE2,EI_LINKEDFILE,
		0,8,32,32);

	for(a = 0;a < 10;a ++){
		sprintf(s,CR_DATADIR1"logo%02d.acf",a);
		JukeLogo[a].ReadFile(s,CR_DATAFILE1,EI_LINKEDFILE);
	}
	//--------------------------------------

	crdataSetGameUsing(&GameUsingData);
	CresteajuReadINIFile(crdataGetIniFile());
	crdataGetIniFile()->UseMIDI = 1;
	//--------------------------------------

	if(crmusicInitMusic() == 0){
		return 0;
	}

	//--------------------------------------
	memset(MusicFlag,0,sizeof(MusicFlag));
	memset(MusicTable,0,sizeof(MusicTable));

	for(a = 0;a < 16;a ++){
		crfileLoadData(a,SAVE_FILE_ID1,SAVE_FILE_ID2,16);

		for(b = 0;strcmp(crmusicGetTitleString()[b],"-silent-") != 0;b ++){
			if(pGameInfo->Music[b])
				MusicFlag[b] = 1;
		}

		if(critemGetItemCount(211) > 0){
			item = 1;
		}
	}
	//--------------------------------------

	if(item){
		check = DialogBox( hThisInst,"Juke",NULL,(DLGPROC)JukeFunc);
	} else {
		ShowError("CresJuke!!を使えるセーブデータがありません");
	}

	//--------------------------------------
	for(a = 0;a < 8;a ++){
		JukeCell[a].Release();
	}
	for(a = 0;a < 10;a ++){
		JukeLogo[a].Release();
	}
	crmusicEndMusic();

	return 0;
}

void JukePlay(HWND hwnd,int number)
{
	SetDlgItemText(hwnd,IDC_COMMENT,JukeComment[number - 1]);

	if(crdataGetIniFile()->MIDIType >= 0){
		crmusicPlay(CRMUSIC_INIT);
		eiSleep(1500);
	}

	crmusicPlay(number,1,CRMUSIC_LOADFORCE);
}

#define JUKETIMER_ID 256
#define LOGOTIMER_ID 255

void JukeEnd(HWND hwnd)
{
	KillTimer(hwnd,JUKETIMER_ID);
	KillTimer(hwnd,LOGOTIMER_ID);

	EndDialog(hwnd,1);
}

extern LPSMIDI_STREAM pMidiStream[STREAM_MAX];

BOOL CALLBACK JukeFunc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int a,tempo,offset = 0;
	static logo_num = 0,logo_mode = 0;
	static int TimerTempo = 120,Character = 0,AnimePos = 0;
	static int first = 1,number = 0,max,PlayFlag = 0;
	HWND hpic;
	HDC hdc;
	POINT point,cur;

	switch(message){
	case WM_TIMER:

		if(wParam == LOGOTIMER_ID){
			hpic = GetDlgItem(hwnd,IDC_CRESLOGO);
			hdc = GetDC(hpic);

			if(logo_mode == 0){
				if(++ logo_num >= 9){
					logo_num = 9;
					logo_mode = 1;
				}
/*			} else if(logo_mode == 1){
				if(-- logo_num <= 7){
					logo_mode = 0;
				}*/
			}

			JukeLogo[logo_num].dib.CopyToDC(hdc,0,0);

			ReleaseDC(hpic,hdc);

			return 1;
		}

		if(PlayFlag){
			offset = 4;
		} else {
			offset = 4;
		}

		hpic = GetDlgItem(hwnd,IDC_CHARA);
		hdc = GetDC(hpic);

		point.x = 16;
		point.y = 16;
		ClientToScreen(hpic,&point);
		GetCursorPos(&cur);
		cur.x -= point.x;
		cur.y -= point.y;
		if(cur.y < 0 && eiAbs(cur.x) < eiAbs(cur.y))
			offset = 0;
		else if(0 < cur.x && eiAbs(cur.y) < eiAbs(cur.x))
			offset = 2;
		else if(0 < cur.y && eiAbs(cur.x) < eiAbs(cur.y))
			offset = 4;
		else// if(0 < cur.x && eiAbs(cur.y) < eiAbs(cur.x))
			offset = 6;

		JukeCell[AnimePos + offset].dib.CopyToDC(hdc,0,0);
		ReleaseDC(hpic,hdc);

		if(PlayFlag && pMidiStream[0] != NULL){
			tempo = pMidiStream[0]->Tempo;
			if(tempo != 0){
				if(60 * 1000000 / tempo){
					if(60 * 1000000 / tempo != TimerTempo){
						int t = (tempo / (1000 * 60));
						if(t != 0){
							TimerTempo = 1000 / t;
							if(TimerTempo != 0){
								KillTimer(hwnd,JUKETIMER_ID);
								SetTimer(hwnd,JUKETIMER_ID,(60 * 1000 / TimerTempo) / 2,NULL);
							}
						}
					}
				}
			}
		}

		if(PlayFlag){
			if(++AnimePos >= 2)
				AnimePos = 0;
		}

		return 1;

	case WM_INITDIALOG:
		if(first){

			SetTimer(hwnd,JUKETIMER_ID,100,NULL);
			SetTimer(hwnd,LOGOTIMER_ID,200,NULL);
			crmusicPlay(CRMUSIC_INIT);
			eiSleep(1500);

			for(a = 1,max = 0;strcmp(crmusicGetTitleString()[a],"-silent-") != 0;a ++){
				if(MusicFlag[a]){
					SendDlgItemMessage(hwnd,IDC_LIST,CB_ADDSTRING,
						0,(LPARAM)crmusicGetTitleString()[a]);

					MusicTable[max] = a;

					max ++;
				}
			}
			first = 0;
		}

		SendDlgItemMessage(hwnd,IDC_LIST,CB_SETCURSEL,
			0,0);

		return 1;
	case WM_CLOSE:
		JukeEnd(hwnd);
		return 1;

	case WM_COMMAND:
		switch(LOWORD(wParam)){
		case IDOK:
		case IDC_JUKEEND:
			JukeEnd(hwnd);
			return 1;

		case IDC_STOP:
			crmusicStop();
			PlayFlag = 0;
			return 1;

		case IDC_PLAY:
			number = SendDlgItemMessage(hwnd,IDC_LIST,CB_GETCURSEL,
				0,0);
			JukePlay(hwnd,MusicTable[number]);
			PlayFlag = 1;
			return 1;

		case IDC_BEFORE:
			number = SendDlgItemMessage(hwnd,IDC_LIST,CB_GETCURSEL,
				0,0);
			if(--number < 0)
				number = max - 1;
			SendDlgItemMessage(hwnd,IDC_LIST,CB_SETCURSEL,
				number,0);
			JukePlay(hwnd,MusicTable[number]);
			PlayFlag = 1;
			return 1;

		case IDC_NEXT:
			number = SendDlgItemMessage(hwnd,IDC_LIST,CB_GETCURSEL,
				0,0);
			if(++number >= max)
				number = 0;
			SendDlgItemMessage(hwnd,IDC_LIST,CB_SETCURSEL,
				number,0);
			JukePlay(hwnd,MusicTable[number]);
			PlayFlag = 1;

			return 1;


		case IDC_ABOUT:
			DialogBox( hThisInst,"JukeAbout",hwnd,(DLGPROC)JukeAboutFunc);
			return 1;

		}
		break;
	}
	return 0;
}


BOOL CALLBACK JukeAboutFunc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message){
	case WM_CLOSE:
		EndDialog(hwnd,1);
		return 1;

	case WM_COMMAND:
		switch(LOWORD(wParam)){
		case IDOK:
			EndDialog(hwnd,1);
			return 1;
		}
	}
	return 0;
}
