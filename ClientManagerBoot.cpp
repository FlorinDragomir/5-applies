///search:
				"applytype0, applyvalue0, applytype1, applyvalue1, applytype2, applyvalue2, "

///replace:
				"applytype0, applyvalue0, applytype1, applyvalue1, applytype2, applyvalue2, applytype3, applyvalue3, applytype4, applyvalue4, "

///search:
				"%d, %ld, %d, %ld, %d, %ld, " or "%u, %ld, %u, %ld, %u, %ld, "

///replace:
				"%d, %ld, %d, %ld, %d, %ld, %d, %ld, %d, %ld, " or "%u, %ld, %u, %ld, %u, %ld, %u, %ld, %u, %ld, "


///if you have InitializeItemTableFromDB

///search:
		" applytype0, applyvalue0, applytype1, applyvalue1, applytype2, applyvalue2,"

///replace:
		" applytype0, applyvalue0, applytype1, applyvalue1, applytype2, applyvalue2, applytype3, applyvalue3, applytype4, applyvalue4,"

///search:
		VERIFY_IFIELD(IProto::applytype2,		item_table->aApplies[2].bType);
		VERIFY_IFIELD(IProto::applyvalue2,		item_table->aApplies[2].lValue);

///add:
		VERIFY_IFIELD(IProto::applytype3,		item_table->aApplies[3].bType);
		VERIFY_IFIELD(IProto::applyvalue3,		item_table->aApplies[3].lValue);
		VERIFY_IFIELD(IProto::applytype4,		item_table->aApplies[4].bType);
		VERIFY_IFIELD(IProto::applyvalue4,		item_table->aApplies[4].lValue);