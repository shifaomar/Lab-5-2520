/*
 * Simple binary search of an array of floats
 * presented as a generic array of void *
 * containing print statements indicating
 * the search state as we proceed
 */

#include <stdio.h>
#include <string.h> // for strcmp()

#include "bsearch-verbose.h"
#include "FruitData.h"

/**
 * Comparator function for generic search based on the latin name in a pointer to pointer
 */
static int pointerComparator_LatinName(const void *vKey, const void *vData)
{
	FruitData **fruitData = (FruitData **)vData;
	char *key = (char *)vKey;
	int result;

	printf(" = = pointerComparator_LatinName: vKey = %p, vData = %p\n", vKey, vData);

	// Compare the key to the "latin" field in the data referenced by the pointer that the *data" passed in here *points at*.
	// That is, the data in the struct pointed to by the pointer *the data pointer is pointing at*.

	result = strcmp(key, (*fruitData)->latin);

	printf(" = = pointerComparator_LatinName: key = %s\n", key);
	printf(" = = pointerComparator_LatinName: fruit = %s, %s\n",
		   (*fruitData)->common, (*fruitData)->latin);
	printf(" = = pointerComparator_LatinName: comparison of (%s/%s) returns %d\n",
		   key, (*fruitData)->latin, result);

	return result;
}

void searchInLatinName(FruitData *const *fruitDataPointers, int nFruits, char *key)
{
	FruitData **pointerResult = NULL;
	int arrayIndex;

	printf("Latin names in array of %d pointers to structs:\n", nFruits);
	printDataPointerArray(fruitDataPointers, nFruits);

	printf("Demonstration of comparator (comparing key to first data element):\n");
	printf("Entering binary search.\n");
	pointerComparator_LatinName(key, fruitDataPointers);

	printf("Entering binary search.\n");

	// Call the binary search with the array of pointers to pointers to the data, the appropriate size, and the comparator above
	pointerResult = binarysearch(key, fruitDataPointers, nFruits, sizeof(FruitData *), pointerComparator_LatinName);

	if (pointerResult != NULL)
	{
		arrayIndex = pointerResult - fruitDataPointers;
		printf("Latin name search using '%s' returned:\n\t", key);
		printFuitWithID(*pointerResult, arrayIndex);
	}
	else
	{
		printf("Latin name search using '%s' FAILED\n", key);
	}
}