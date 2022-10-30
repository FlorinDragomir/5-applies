///search:
bool Set_Proto_Item_Table(TItemTable* itemTable, cCsvTable& csvTable, std::map<int, const char*>& nameMap)
{
	[...]
}


///replace or adapt:
bool Set_Proto_Item_Table(TItemTable *itemTable, cCsvTable &csvTable,std::map<int,const char*> &nameMap)
{
int col = 0;
	int dataArray[37];
	for (unsigned int i=0; i<sizeof(dataArray)/sizeof(dataArray[0]);i++) {
		int validCheck = 0;
		if (i==2) {
			dataArray[i] = get_Item_Type_Value(csvTable.AsStringByIndex(col));
			validCheck = dataArray[i];
		} else if (i==3) {
			dataArray[i] = get_Item_SubType_Value(dataArray[i-1], csvTable.AsStringByIndex(col));
			validCheck = dataArray[i];
		} else if (i==5) {
			dataArray[i] = get_Item_AntiFlag_Value(csvTable.AsStringByIndex(col));
			validCheck = dataArray[i];
		} else if (i==6) {
			dataArray[i] = get_Item_Flag_Value(csvTable.AsStringByIndex(col));
			validCheck = dataArray[i];
		} else if (i==7) {
			dataArray[i] = get_Item_WearFlag_Value(csvTable.AsStringByIndex(col));
			validCheck = dataArray[i];
		} else if (i==8) {
			dataArray[i] = get_Item_Immune_Value(csvTable.AsStringByIndex(col));
			validCheck = dataArray[i];
		} else if (i==14) {
			dataArray[i] = get_Item_LimitType_Value(csvTable.AsStringByIndex(col));
			validCheck = dataArray[i];
		} else if (i==16) {
			dataArray[i] = get_Item_LimitType_Value(csvTable.AsStringByIndex(col));
			validCheck = dataArray[i];
		} else if (i==18) {
			dataArray[i] = get_Item_ApplyType_Value(csvTable.AsStringByIndex(col));
			validCheck = dataArray[i];
		} else if (i==20) {
			dataArray[i] = get_Item_ApplyType_Value(csvTable.AsStringByIndex(col));
			validCheck = dataArray[i];
		} else if (i==22) {
			dataArray[i] = get_Item_ApplyType_Value(csvTable.AsStringByIndex(col));
			validCheck = dataArray[i];
		} else if (i==24) {
			dataArray[i] = get_Item_ApplyType_Value(csvTable.AsStringByIndex(col));
			validCheck = dataArray[i];
		} else if (i==26) {
			dataArray[i] = get_Item_ApplyType_Value(csvTable.AsStringByIndex(col));
			validCheck = dataArray[i];
		} else {
			str_to_number(dataArray[i], csvTable.AsStringByIndex(col));
		}
		if (validCheck == -1)
		{
			std::ostringstream dataStream;
			for (unsigned int j = 0; j < i; ++j)
				dataStream << dataArray[j] << ",";
			sys_err("ItemProto Reading Failed : Invalid value. (index: %d, col: %d, value: %s)", i, col, csvTable.AsStringByIndex(col));
			sys_err("\t%d ~ %d Values: %s", 0, i, dataStream.str().c_str());
			exit(0);
		}
		col = col + 1;
	}
	std::string s(csvTable.AsStringByIndex(0));
	unsigned int pos = s.find("~");
	if (std::string::npos == pos)
	{
		itemTable->dwVnum = dataArray[0];
		itemTable->dwVnumRange = 0;
	}
	else
	{
		std::string s_start_vnum (s.substr(0, pos));
		std::string s_end_vnum (s.substr(pos +1 ));

		int start_vnum = atoi(s_start_vnum.c_str());
		int end_vnum = atoi(s_end_vnum.c_str());
		if (0 == start_vnum || (0 != end_vnum && end_vnum < start_vnum))
		{
			sys_err ("INVALID VNUM %s", s.c_str());
			return false;
		}
		itemTable->dwVnum = start_vnum;
		itemTable->dwVnumRange = end_vnum - start_vnum;
	}
	strlcpy(itemTable->szName, csvTable.AsStringByIndex(1), sizeof(itemTable->szName));
	map<int,const char*>::iterator it;
	it = nameMap.find(itemTable->dwVnum);
	if (it != nameMap.end()) {
		const char * localeName = it->second;
		strlcpy(itemTable->szLocaleName, localeName, sizeof (itemTable->szLocaleName));
	} else {
		strlcpy(itemTable->szLocaleName, itemTable->szName, sizeof (itemTable->szLocaleName));
	}
	itemTable->bType = dataArray[2];
	itemTable->bSubType = dataArray[3];
	itemTable->bSize = dataArray[4];
	itemTable->dwAntiFlags = dataArray[5];
	itemTable->dwFlags = dataArray[6];
	itemTable->dwWearFlags = dataArray[7];
	itemTable->dwImmuneFlag = dataArray[8];
	itemTable->dwGold = dataArray[9];
	itemTable->dwShopBuyPrice = dataArray[10];
	itemTable->dwRefinedVnum = dataArray[11];
	itemTable->wRefineSet = dataArray[12];
	itemTable->bAlterToMagicItemPct = dataArray[13];
	itemTable->cLimitRealTimeFirstUseIndex = -1;
	itemTable->cLimitTimerBasedOnWearIndex = -1;
	int i;
	for (i = 0; i < ITEM_LIMIT_MAX_NUM; ++i)
	{
		itemTable->aLimits[i].bType = dataArray[14+i*2];
		itemTable->aLimits[i].lValue = dataArray[15+i*2];
		if (LIMIT_REAL_TIME_START_FIRST_USE == itemTable->aLimits[i].bType)
			itemTable->cLimitRealTimeFirstUseIndex = (char)i;
		if (LIMIT_TIMER_BASED_ON_WEAR == itemTable->aLimits[i].bType)
			itemTable->cLimitTimerBasedOnWearIndex = (char)i;

	}
	for (i = 0; i < ITEM_APPLY_MAX_NUM; ++i)
	{
		itemTable->aApplies[i].bType = dataArray[18+i*2];
		itemTable->aApplies[i].lValue = dataArray[19+i*2];
	}
	for (i = 0; i < ITEM_VALUES_MAX_NUM; ++i)
		itemTable->alValues[i] = dataArray[28+i];
	itemTable->bGainSocketPct = dataArray[35];
	itemTable->sAddonType = dataArray[36];
	str_to_number(itemTable->bWeight, "0");
	return true;
}

