///search:
	ITEM_APPLY_MAX_NUM			= 3,

///replace:
	ITEM_APPLY_MAX_NUM			= 5,

///search:
void LoadItemProto()
{
	[...]
}

///replace or adapt:
void LoadItemProto()
{
	FILE * fp;
	DWORD fourcc, tableSize, dataSize, protoVersion, structSize;

	fp = fopen("item_proto", "rb");
	if (fp==NULL)
	{
		printf("item_proto not found");
		return;
	}
	

	fread(&fourcc, sizeof(DWORD), 1, fp);
	fread(&protoVersion, sizeof(DWORD), 1, fp);
	fread(&structSize, sizeof(DWORD), 1, fp);
	fread(&tableSize, sizeof(DWORD), 1, fp);
	fread(&dataSize, sizeof(DWORD), 1, fp);
	BYTE * data = (BYTE *) malloc(dataSize);

	if (data)
	{
		fread(data, dataSize, 1, fp);

		CLZObject zObj;

		if (CLZO::instance().Decompress(zObj, data, g_adwItemProtoKey))
		{
			printf("real_size %u\n", zObj.GetSize());

			if (LoadNPrint)
			{
				for (DWORD i = 0; i < tableSize; ++i)
				{
					TClientItemTable & rTable = *((TClientItemTable *) zObj.GetBuffer() + i);
					printf("%u %s\n", rTable.dwVnum, rTable.szLocaleName);
				}
			}
			else
			{
				FILE * mf1 = fopen("item_names.txt", "w");
				FILE * mf2 = fopen("item_proto.txt", "w");
				if (mf1==NULL)
				{
					printf("item_names.txt not writable");
					return;
				}
				if (mf2==NULL)
				{
					printf("item_proto.txt not writable");
					return;
				}
				fprintf(mf1, "VNUM\tLOCALE_NAME\n");
				fprintf(mf2, "ITEM_VNUM~RANGE\tITEM_NAME(K)\tITEM_TYPE\tSUB_TYPE\tSIZE\tANTI_FLAG\tFLAG\tITEM_WEAR\tIMMUNE\tGOLD\tSHOP_BUY_PRICE\tREFINE\tREFINESET\tMAGIC_PCT\tLIMIT_TYPE0\tLIMIT_VALUE0\tLIMIT_TYPE1\tLIMIT_VALUE1\tADDON_TYPE0\tADDON_VALUE0\tADDON_TYPE1\tADDON_VALUE1\tADDON_TYPE2\tADDON_VALUE2\tADDON_TYPE3\tADDON_VALUE3\tADDON_TYPE4\tADDON_VALUE4\tVALUE0\tVALUE1\tVALUE2\tVALUE3\tVALUE4\tVALUE5\tSpecular\tSOCKET\tATTU_ADDON"
#if defined(ENABLE_NEW_ITEM_PROTO_STRUCT_20160129) && !defined(USE_NEW_ITEM_PROTO_STRUCT_20160129_ONLY_WHEN_UNPACKING)
					"\tWEARABLE_FLAG"
#endif
					"\n"
				);
				for (DWORD i = 0; i < tableSize; ++i)
				{
					TClientItemTable & rTable = *((TClientItemTable *) zObj.GetBuffer() + i);
					fprintf(mf1, "%u	%s\n", rTable.dwVnum, rTable.szLocaleName);
					fprintf(mf2,
						"%s	" 	// 1
						"%s" 	// 2
						"	%s" // 3
						"	%s" // 4
						"	%u" // 5
						"	%s" // 6
						"	%s" // 7
						"	%s" // 8
						"	%s" // 9
						"	%u" // 10
						"	%u" // 11
						"	%u" // 12
						"	%u" // 13
						"	%u" // 14
						"	%s" // 15
						"	%d" // 16
						"	%s" // 17
						"	%d" // 18
						"	%s" // 19
						"	%d" // 20
						"	%s" // 21
						"	%d" // 22
						"	%s" // 23
						"	%d" // 24
						"	%s" // 25
						"	%d" // 26
						"	%s" // 27
						"	%d" // 28
						"	%d" // 29
						"	%d" // 30
						"	%d" // 31
						"	%d" // 32
						"	%d" // 33
						"	%d" // 34
						"	%u" // 35
						"	%u" // 36
						"	%d" // 37
#if defined(ENABLE_NEW_ITEM_PROTO_STRUCT_20160129) && !defined(USE_NEW_ITEM_PROTO_STRUCT_20160129_ONLY_WHEN_UNPACKING)
						"	%d" // 38
#endif
						"\n",
						retrieveVnumRange(rTable.dwVnum, rTable.dwVnumRange).c_str(),                   // 1
						rTable.szName, 																	// 2
						set_Item_Type_Value(rTable.bType).c_str(),                                      // 3
						set_Item_SubType_Value(rTable.bType, rTable.bSubType).c_str(),                  // 4
						rTable.bSize,                                                                   // 5
						set_Item_AntiFlag_Value(rTable.dwAntiFlags).c_str(), 							// 6
						set_Item_Flag_Value(rTable.dwFlags).c_str(),                                    // 7
						set_Item_WearFlag_Value(rTable.dwWearFlags).c_str(),                            // 8
						set_Item_Immune_Value(rTable.dwImmuneFlag).c_str(), 							// 9
						rTable.dwGold,                                                                  // 10
						rTable.dwShopBuyPrice,                                                          // 11
						rTable.dwRefinedVnum,                                                           // 12
						rTable.wRefineSet,                                                              // 13
						rTable.bAlterToMagicItemPct, 													// 14
						set_Item_LimitType_Value(rTable.aLimits[0].bType).c_str(),                      // 15
						rTable.aLimits[0].lValue,                                                       // 16
						set_Item_LimitType_Value(rTable.aLimits[1].bType).c_str(),                      // 17
						rTable.aLimits[1].lValue, 														// 18
						set_Item_ApplyType_Value(rTable.aApplies[0].bType).c_str(),                     // 19
						rTable.aApplies[0].lValue,                                                      // 20
						set_Item_ApplyType_Value(rTable.aApplies[1].bType).c_str(),                     // 21
						rTable.aApplies[1].lValue,                                                      // 22
						set_Item_ApplyType_Value(rTable.aApplies[2].bType).c_str(),                     // 23
						rTable.aApplies[2].lValue, 														// 24
						set_Item_ApplyType_Value(rTable.aApplies[3].bType).c_str(),                     // 25
						rTable.aApplies[3].lValue, 														// 26
						set_Item_ApplyType_Value(rTable.aApplies[4].bType).c_str(),                     // 27
						rTable.aApplies[4].lValue, 														// 28
						rTable.alValues[0],                                                             // 29
						rTable.alValues[1],                                                             // 30
						rTable.alValues[2],                                                             // 31
						rTable.alValues[3],                                                             // 32
						rTable.alValues[4],                                                             // 33
						rTable.alValues[5], 															// 34
						rTable.bSpecular,                                                               // 35
						rTable.bGainSocketPct,                                                          // 36
						retrieveAddonType(rTable.dwVnum) 												// 37
#if defined(ENABLE_NEW_ITEM_PROTO_STRUCT_20160129) && !defined(USE_NEW_ITEM_PROTO_STRUCT_20160129_ONLY_WHEN_UNPACKING)
						, rTable.wWearableFlag															// 38
#endif
					);
				}
				;
			}
		}

		free(data);
	}

	fclose(fp);
}

