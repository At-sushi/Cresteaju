typedef struct
{
	float left,top,right,bottom;
} FRECT;

CRBATTLEDRAW_API void crbatBeginCameraObjectToObject(
					int camera,
					CrBattleCharacter *pSrc,CrBattleCharacter *pDst,
					float RotateAngle,float DeltaSrcR /*= -1*/,float DeltaDstR /* = -1*/,
					int run_time /*= 250*/)
{
	//---２点間の距離
	float dx,dy,angle;
	//---回転軸中心座標
	float cx,cy;
	//---２点間を結ぶ直線の延長距離
	float R;
	float SrcZ = 4.0f,DstZ = 0.0f;

/*	if(pSrc == pDst){
		//---対象が自分自身の場合は
		pSrc->BeginMovingCameraFront(camera);
		return;
	}*/

	if(DeltaSrcR < 0.0f)
		DeltaSrcR = 2.0f;
	if(DeltaDstR < 0.0f)
		DeltaDstR = 2.0f;

	//---２点間の角度
	angle = crbatGetCameraAngle(
		(float)pSrc->GetFieldX(),(float)pSrc->GetFieldY(),
		(float)pDst->GetFieldX(),(float)pDst->GetFieldY());

	float csrc_x,csrc_y,cdst_x,cdst_y;
	csrc_x = (float)pSrc->GetFieldX() + (float)(cos(angle + PI) * DeltaSrcR);
	csrc_y = (float)pSrc->GetFieldY() + (float)(sin(angle + PI) * DeltaSrcR);
	cdst_x = (float)pDst->GetFieldX() + (float)(cos(angle) * DeltaDstR);
	cdst_y = (float)pDst->GetFieldY() + (float)(sin(angle) * DeltaDstR);

	dx = (float)(cdst_x - csrc_x);
	dy = (float)(cdst_y - csrc_y);
	cx = (float)(dx / 2.0f + csrc_x);
	cy = (float)(dy / 2.0f + csrc_y);
	R = (float)sqrt(dx * dx + dy * dy);

	angle += (float)RotateAngle;
	//---0-360に角度補正
	CALC_ANGLE(angle);

	crbatBeginMovingCamera(
		camera,
		(float)cx + (float)(cos(angle + PI) * (R /*+ DeltaSrcR*/)),
		(float)cy + (float)(sin(angle + PI) * (R /*+ DeltaSrcR*/)),
		(float)SrcZ,
		(float)cx + (float)(cos(angle ) * (R /*+ DeltaDstR*/)),
		(float)cy + (float)(sin(angle ) * (R /*+ DeltaDstR*/)),
		(float)DstZ);

/*	char s[100];
	sprintf(s,"%s : %s , %f\n",pSrc->GetName(),pDst->GetName(),angle);
	eiDebugWriteFile(s);*/

//	crbatDoMovingCamera(run_time);
}

//-----------------------------------------------
//---ビューをなめらかに変更
CRBATTLEDRAW_API void crbatChangeSlowView(int DstMode,int run_time /*= 250*/)
{
	RECT SrcRect = BattleViewRect[BattleViewMode][0],
		 DstRect = BattleViewRect[DstMode][0],
		 TempRect;
	FRECT DeltaRect,ChangeRect;
	float AddWorld = 0.0f;
	eiTime let;
	int Start = let.GetTime();

	if(BattleViewMode == DstMode)
		return;

	DeltaRect.left   = (float)(DstRect.left - SrcRect.left) / (float)run_time;
	DeltaRect.right  = (float)(DstRect.right - SrcRect.right) / (float)run_time;
	DeltaRect.top    = (float)(DstRect.top - SrcRect.top) / (float)run_time;
	DeltaRect.bottom = (float)(DstRect.bottom - SrcRect.bottom) / (float)run_time;
	ChangeRect.left   = (float)SrcRect.left;
	ChangeRect.right  = (float)SrcRect.right;
	ChangeRect.top    = (float)SrcRect.top;
	ChangeRect.bottom = (float)SrcRect.bottom;

	if(crsysQuick() || !crdataGetSystem()->BattleMoveCamera){
		//---クイックか、カメラ移動が禁止されていれば
		AddWorld = (float)run_time;
		run_time = -1; 
	}

	crbatSetViewMode(BATTLE_VIEWMODE_TEMP);

	while(1){
		let.Reset();
		if(let.GetTime() - Start < run_time){
			//---進んだ時間だけ増加
			ChangeRect.left   += (float)(DeltaRect.left * AddWorld);
			ChangeRect.right  += (float)(DeltaRect.right * AddWorld);
			ChangeRect.top    += (float)(DeltaRect.top * AddWorld);
			ChangeRect.bottom += (float)(DeltaRect.bottom * AddWorld);

			TempRect.left   = (int)ChangeRect.left;
			if(TempRect.left < 0)
				TempRect.left = 0;

			TempRect.right  = (int)ChangeRect.right;
			if(TempRect.right >= 640)
				TempRect.right = 639;

			TempRect.top    = (int)ChangeRect.top;
			if(TempRect.top < 0)
				TempRect.top = 0;

			TempRect.bottom = (int)ChangeRect.bottom;
			if(TempRect.bottom >= 480)
				TempRect.bottom = 479;

			BattleViewRect[BATTLE_VIEWMODE_TEMP][0] = TempRect;
			HViewNumber[BATTLE_VIEWMODE_TEMP] =
				((float)BattleViewRect[BATTLE_VIEWMODE_SINGLE][0].right / (float)TempRect.right) * 4.0f;

/*			char s[80];
			sprintf(s,"%d ,%d ,%d ,%d  %f\n",
				BattleViewRect[BATTLE_VIEWMODE_TEMP][0].left,
				BattleViewRect[BATTLE_VIEWMODE_TEMP][0].top,
				BattleViewRect[BATTLE_VIEWMODE_TEMP][0].right,
				BattleViewRect[BATTLE_VIEWMODE_TEMP][0].bottom,
				HViewNumber[BATTLE_VIEWMODE_TEMP]);
			eiDebugWriteFile(s);*/

			//---描く！
			ew->lpCell[1]->DrawFillBox(0,0,640,256 + 16,ep->ToRGB(CRCOLOR_BLACK));

			crbatDrawScene();
			crbatDrawRefresh();
		} else {
			//---描く！
			crbatSetViewMode(DstMode);
			ew->lpCell[1]->DrawFillBox(0,0,640,256 + 16,ep->ToRGB(CRCOLOR_BLACK));

			crbatDrawScene();
			crbatDrawRefresh();
			break;
		}

		AddWorld = (float)let.Get();
	}

	crbatSetViewMode(DstMode);
}

//---対象物に応じて視点切り換え
CRBATTLEDRAW_API int crbatSetCameraWithObject(CrBattleCharacter *pChara,
						CrBattleCharacter **ppList,int run_time /*= 500*/,
						CrBattleCharacter **ppReturnCenter /* = NULL*/)
{
	int ret = 0;
	static angle_count = 0;
	float AngleTable[] = {
		ANGLE(270),ANGLE(90),ANGLE(0),ANGLE(180),
		ANGLE(90),ANGLE(270),ANGLE(180),ANGLE(0),
	};
	float SubAngleTable[] = {ANGLE(8),ANGLE(-8)};
	int camera_angle = crdataGetSystem()->BattleCameraAngle * 2;

	if(angle_count >= 2)
		angle_count = 0;

	if(pChara->Command.Main == BAT_COMMAND_DEFENSE){
		if(pChara->Command.Sub[0] == BAT_SUBCOM_MOVE){
			//---移動だったら
//			CrBattleCharacter tempobj;
			CrBattleCharacter *ptempobj = &pBtTempChara[2];
			pBtTempChara[2].InitBattleCharacter();
			//---移動先に透明オブジェクト
			ptempobj->SetFieldPos(pChara->Command.Sub[1],pChara->Command.Sub[2]);

			//---シングルビューの場合
			crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
			crbatBeginCameraObjectToObject(0,pChara,ptempobj,
			AngleTable[(pChara->IsFriend() ? 0 : 1) + camera_angle] + SubAngleTable[angle_count % 2],
			-1.0f,-1.0f,
			500);
			//---リストに描くのを追加
			crbatClearDrawingList();
			crbatAddDrawingListAll();

			angle_count ++;
			return 1;
		}
	} else if(ppList[1] == NULL
		(pChara->Command.Range & BAT_TARGET_SINGLE)
/*		|| (BAT_RANGE_LINE1 <= (pChara->Command.Range & 0xff0000) && (pChara->Command.Range & 0xff0000) <= BAT_RANGE_LINE6)*/
		){
		//---相手が一人、またはラインターゲットの場合
		{
			//---シングルビューの場合
			crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
			crbatBeginCameraObjectToObject(0,pChara,ppList[0],
			AngleTable[(pChara->IsFriend() ? 0 : 1) + camera_angle] + SubAngleTable[angle_count % 2],
			-1.0f,-1.0f,
			500);
			//---リストに描くのを追加
			crbatClearDrawingList();
			crbatAddDrawingListAll();

			angle_count ++;
			return 1;
		}

		//---ダブルビューの場合
		crbatChangeSlowView(BATTLE_VIEWMODE_DOUBLE);

//		if(crbatGetViewMode() == BATTLE_VIEWMODE_DOUBLE){
			pChara->BeginMovingCameraFront(0);
			ppList[0]->BeginMovingCameraFront(1);
			ret = 1;
/*		} else {
			crbatSetViewMode(BATTLE_VIEWMODE_DOUBLE);
			pChara->SetCameraFront(0);
			ppList[0]->SetCameraFront(1);
			ret = 0;
		}*/

		//---リストに描くのを追加
		crbatClearDrawingList();
		crbatAddDrawingListAll();
/*	} else if(pChara->Command.Range & BAT_TARGET_ALLTARGET){
		crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
		crbatSetCamera_ViewBattleField( 0,AngleTable[(pChara->IsFriend() ? 0 : 1) + camera_angle] + SubAngleTable[angle_count % 2],2,500);

		crbatClearDrawingList();
		crbatAddDrawingListAll();
		return 1;*/
	} else {
//	} else if((BAT_RANGE_CIRCLE1 <= (pChara->Command.Range & 0xff0000) && (pChara->Command.Range & 0xff0000) <= BAT_RANGE_CIRCLE6)){
		CrBattleCharacter *pCenter = ppList[0],**pptemp = &ppList[1];
		float dist = pChara->GetDistance(ppList[0]);

		//---一番遠い目標を探す
		for(pptemp = ppList;pptemp[0] != NULL;pptemp ++){
			if(pChara->GetDistance(pptemp[0]) > dist){
				dist = pChara->GetDistance(pptemp[0]);
				pCenter = pptemp[0];
			}
		}

		//---サークルターゲット
		crbatChangeSlowView(BATTLE_VIEWMODE_SINGLE);
		crbatBeginCameraObjectToObject(0,pChara,pCenter,
			AngleTable[(pChara->IsFriend() ? 0 : 1) + camera_angle] + SubAngleTable[angle_count % 2],
			-1.0f,
			//*(float)((float)BattleCircleRange[((pChara->Command.Range & 0xff0000) >> 16 ) - BAT_RANGE_CIRCLESTART]) / 2.0f + 2.0f*/
			-1.0f,
			500);
		//---リストに描くのを追加
		crbatClearDrawingList();
		crbatAddDrawingListAll();

		if(ppReturnCenter != NULL){
			//---どのキャラ中心か、返す
			*ppReturnCenter = pCenter;
		}

		angle_count ++;
		return 1;
	}

	return ret;
}

//---カメラをある地点へ向けて動かす
#define DIVIDE(x) {\
		x /= (run_time);\
	}\

static float st_cx[4],st_cy[4],st_cz[4],st_dx[4],st_dy[4],st_dz[4];
static float dcx[4],dcy[4],dcz[4],ddx[4],ddy[4],ddz[4];
static float ccx[4],ccy[4],ccz[4],cdx[4],cdy[4],cdz[4];
static float end_cx[4],end_cy[4],end_cz[4],end_dx[4],end_dy[4],end_dz[4];
static float start_angle[4],cangle[4],dangle[4],end_angle[4];

//---カメラ移動開始
CRBATTLEDRAW_API void crbatBeginMovingCamera(
			int camera,
			float cx,float cy,float cz,
			float dx,float dy,float dz)
{
	st_cx[camera] = BattleView[camera].cx;
	st_cy[camera] = BattleView[camera].cy;
	st_cz[camera] = BattleView[camera].cz;
	st_dx[camera] = BattleView[camera].dx;
	st_dy[camera] = BattleView[camera].dy;
	st_dz[camera] = BattleView[camera].dz;

	dcx[camera] = cx - BattleView[camera].cx;
	dcy[camera] = cy - BattleView[camera].cy;
	dcz[camera] = cz - BattleView[camera].cz;

	ddx[camera] = dx - BattleView[camera].dx;
	ddy[camera] = dy - BattleView[camera].dy;
	ddz[camera] = dz - BattleView[camera].dz;

	ccx[camera] = BattleView[camera].cx;
	ccy[camera] = BattleView[camera].cy;
	ccz[camera] = BattleView[camera].cz;
	cdx[camera] = BattleView[camera].dx;
	cdy[camera] = BattleView[camera].dy;
	cdz[camera] = BattleView[camera].dz;
	end_cx[camera] = cx;
	end_cy[camera] = cy;
	end_cz[camera] = cz;
	end_dx[camera] = dx;
	end_dy[camera] = dy;
	end_dz[camera] = dz;

	float fcx,fcy,fcz,fdx,fdy,fdz;
	crbatTranslatePos(cx,cy,cz,&fcx,&fcy,&fcz);
	crbatTranslatePos(dx,dy,dz,&fdx,&fdy,&fdz);
	cangle[camera] = start_angle[camera] = BattleView[camera].Angle;
	end_angle[camera] = crbatGetCameraAngle(fcx,fcy,fdx,fdy);
	dangle[camera] = end_angle[camera] - start_angle[camera];
	if(dangle[camera] > (float)PI){
		dangle[camera] = PI * 2.000f - dangle[camera];
	}
}

//---カメラ移動をする
CRBATTLEDRAW_API void crbatDoMovingCamera(int run_time /*= 500*/)
{
	eiTime let;
	int count [] = {1,1,2,1};
	int a,camera_number = count[crbatGetViewMode()],Start = let.GetTime();
	float AddWorld = 0.0f;
	float passed_time = 0.0;

	if(crsysQuick() || !crdataGetSystem()->BattleMoveCamera){
		//---クイックか、カメラ移動が禁止されていれば
		AddWorld = (float)run_time;
		run_time = -1; 
	}

	for(a = 0;a < camera_number;a ++){
		DIVIDE(dcx[a]);
		DIVIDE(dcy[a]);
		DIVIDE(dcz[a]);
		DIVIDE(ddx[a]);
		DIVIDE(ddy[a]);
		DIVIDE(ddz[a]);
		DIVIDE(dangle[a]);
	}

	while(1){
		let.Reset();
		passed_time = (float)(let.GetTime() - Start);

		if(let.GetTime() - Start < run_time){
			//---進んだ時間だけ増加
			for(a = 0;a < camera_number;a ++){
				ccx[a] = (st_cx[a] + dcx[a] * passed_time);
				ccy[a] = (st_cy[a] + dcy[a] * passed_time);
				ccz[a] = (st_cz[a] + dcz[a] * passed_time);

				cdx[a] = (st_dx[a] + ddx[a] * passed_time);
				cdy[a] = (st_dy[a] + ddy[a] * passed_time);
				cdz[a] = (st_dz[a] + ddz[a] * passed_time);

				cangle[a] += (float)(dangle[a] * AddWorld);

				crbatSetCamera(a,
					ccx[a],ccy[a],ccz[a],
					cdx[a],cdy[a],cdz[a]);
			}

			//---描く！
crdataEnableRec(0);
			crbatDrawScene();
crdataEnableRec(1);
			crbatDrawRefresh();
			//ew->Refresh();
		} else {
			for(a = 0;a < camera_number;a ++){
				crbatSetCamera(a,
					end_cx[a],end_cy[a],end_cz[a],
					end_dx[a],end_dy[a],end_dz[a]);
			}
			//---描く！
crdataEnableRec(0);
			crbatDrawScene();
crdataEnableRec(1);
			crbatDrawRefresh();
			//ew->Refresh();
			break;
		}


		AddWorld = (float)let.Get();
	}
}

CRBATTLEDRAW_API void crbatMoveCamera(int camera,
			float cx,float cy,float cz,
			float dx,float dy,float dz,
			int run_time /*= 500*/)
{
	eiTime let;
	int a,camera_number = 1;
	float dcx[4],dcy[4],dcz[4],ddx[4],ddy[4],ddz[4];
	float ccx[4],ccy[4],ccz[4],cdx[4],cdy[4],cdz[4];
	float passed_time = 0.0;

	float st_cx[4],st_cy[4],st_cz[4],st_dx[4],st_dy[4],st_dz[4];	

	st_cx[camera] = BattleView[camera].cx;
	st_cy[camera] = BattleView[camera].cy;
	st_cz[camera] = BattleView[camera].cz;
	st_dx[camera] = BattleView[camera].dx;
	st_dy[camera] = BattleView[camera].dy;
	st_dz[camera] = BattleView[camera].dz;

	for(a = 0;a < camera_number;a ++){
		dcx[a] = cx - BattleView[camera].cx;
		dcy[a] = cy - BattleView[camera].cy;
		dcz[a] = cz - BattleView[camera].cz;

		ddx[a] = dx - BattleView[camera].dx;
		ddy[a] = dy - BattleView[camera].dy;
		ddz[a] = dz - BattleView[camera].dz;

		ccx[a] = BattleView[camera].cx;
		ccy[a] = BattleView[camera].cy;
		ccz[a] = BattleView[camera].cz;
		cdx[a] = BattleView[camera].dx;
		cdy[a] = BattleView[camera].dy;
		cdz[a] = BattleView[camera].dz;

		DIVIDE(dcx[a]);
		DIVIDE(dcy[a]);
		DIVIDE(dcz[a]);
		DIVIDE(ddx[a]);
		DIVIDE(ddy[a]);
		DIVIDE(ddz[a]);

		float fcx,fcy,fcz,fdx,fdy,fdz;
		crbatTranslatePos(cx,cy,cz,&fcx,&fcy,&fcz);
		crbatTranslatePos(dx,dy,dz,&fdx,&fdy,&fdz);
		cangle[a] = start_angle[a] = BattleView[a].Angle;
		end_angle[a] = crbatGetCameraAngle(fcx,fcy,fdx,fdy);
		dangle[a] = end_angle[a] - start_angle[a];
		if(dangle[a] > (float)PI){
			dangle[a] = PI * 2.000f - dangle[a];
		}
		DIVIDE(dangle[a]);
	}

	int Start = let.GetTime();
	float AddWorld = 0.0f;

	if(crsysQuick() || !crdataGetSystem()->BattleMoveCamera){
		//---クイックか、カメラ移動が禁止されていれば
		AddWorld = (float)run_time;
		run_time = -1; 
	}

	while(1){
		let.Reset();
		passed_time = (float)(let.GetTime() - Start);
		if(let.GetTime() - Start < run_time){
			//---進んだ時間だけ増加
			a = 0;
			{
/*				ccx[a] += (dcx[a] * AddWorld);
				ccy[a] += (dcy[a] * AddWorld);
				ccz[a] += (dcz[a] * AddWorld);

				cdx[a] += (ddx[a] * AddWorld);
				cdy[a] += (ddy[a] * AddWorld);
				cdz[a] += (ddz[a] * AddWorld);
*/
				ccx[a] = (st_cx[a] + dcx[a] * passed_time);
				ccy[a] = (st_cy[a] + dcy[a] * passed_time);
				ccz[a] = (st_cz[a] + dcz[a] * passed_time);

				cdx[a] = (st_dx[a] + ddx[a] * passed_time);
				cdy[a] = (st_dy[a] + ddy[a] * passed_time);
				cdz[a] = (st_dz[a] + ddz[a] * passed_time);

				cangle[a] += (dangle[a] * AddWorld);

				crbatSetCamera(camera,
					ccx[a],ccy[a],ccz[a],
					cdx[a],cdy[a],cdz[a]);

/*				float r;
				r = (float)sqrt((cdx[a] - ccx[a]) * (cdx[a] - ccx[a])
					+ (cdy[a] - ccy[a]) * (cdy[a] - ccy[a]));
				crbatSetCamera(camera,
					ccx[a],ccy[a],ccz[a],
					ccx[a] + r * (float)cos(cangle[a]),
					ccy[a] + r * (float)sin(cangle[a]),cdz[a]);*/
			}

			//---描く！
crdataEnableRec(0);
			crbatDrawScene();
crdataEnableRec(1);
			crbatDrawRefresh();
			//ew->Refresh();
		} else {
			crbatSetCamera(camera,
				cx,cy,cz,
				dx,dy,dz);
			//---描く！
crdataEnableRec(0);
			crbatDrawScene();
crdataEnableRec(1);
			crbatDrawRefresh();
			//ew->Refresh();
			break;
		}

		AddWorld = (float)let.Get();
	}
}
