#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 6

struct package
{
	char* id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight;
	int max_weight;
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char* name;
	post_office* offices;
	int offices_count;
};

typedef struct town town;



void print_all_packages(town t) {
    printf("%s:\r\n", t.name);
    for (int i = 0; i < t.offices_count; i++) {
        printf("\t%d:\r\n", i);
        for (int j = 0; j < t.offices[i].packages_count; j++) {
            printf("\t\t%s\r\n", t.offices[i].packages[j].id);
        }
    }
}

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {	
    post_office* officeSrc = source->offices + source_office_index;
    post_office* officeTgt = target->offices + target_office_index;
    package* arrTemp = (package*)malloc(officeSrc->packages_count * sizeof(package));
    memset(arrTemp, 0, officeSrc->packages_count * sizeof(package));
    int iPassCnt = 0;

    for (int i = 0; i < officeSrc->packages_count; i++) {
        if (officeSrc->packages[i].weight >= officeTgt->min_weight && officeSrc->packages[i].weight <= officeTgt->max_weight) {
            arrTemp[iPassCnt++] = officeSrc->packages[i];
            officeSrc->packages[i].weight = -1;
        }
    }
    int iLeftCnt = 0;
    for (int r = 0; r < officeSrc->packages_count; r++) {
        if (officeSrc->packages[r].weight != -1) {
            memcpy(officeSrc->packages + iLeftCnt, officeSrc->packages + r, sizeof(package));
            iLeftCnt++;
        }
    }
    if (iLeftCnt != officeSrc->packages_count - iPassCnt) {
        printf("Number doesn't match");
    }
    officeSrc->packages_count = iLeftCnt;
    
    officeTgt->packages = (package*)realloc(officeTgt->packages, (officeTgt->packages_count + iPassCnt) * sizeof(package));
    for (int i = 0; i < iPassCnt; i++) {
        memcpy(officeTgt->packages + officeTgt->packages_count + i, arrTemp + i, sizeof(package));
    }
    officeTgt->packages_count += iPassCnt;
}

town town_with_most_packages(town* towns, int towns_count) {
    town* retTown = NULL;
    int iMaxPkgNum = 0;
    for (int i = 0; i < towns_count; i++) {
        int iPkgCnt = 0;
        for (int j = 0; j < towns[i].offices_count; j++) {
            iPkgCnt += towns[i].offices[j].packages_count;
        }
        if (iPkgCnt > iMaxPkgNum) {
            iMaxPkgNum = iPkgCnt;
            retTown = &towns[i];
        }
    }
    return *retTown;
}

town* find_town(town* towns, int towns_count, char* name) {
    for (int i = 0; i < towns_count; i++) {
        if (strcmp(towns[i].name, name) == 0) return &towns[i];
    }
    return NULL;
}

int main()
{
	int towns_count;
	scanf("%d", &towns_count);
	town* towns = (town*)malloc(sizeof(town)*towns_count);
	for (int i = 0; i < towns_count; i++) {
		towns[i].name = (char*)malloc(sizeof(char) * MAX_STRING_LENGTH);
		scanf("%s", towns[i].name);
		scanf("%d", &towns[i].offices_count);
		towns[i].offices = (post_office*)malloc(sizeof(post_office)*towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++) {
			scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = (package*)malloc(sizeof(package)*towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
				towns[i].offices[j].packages[k].id = (char*)malloc(sizeof(char) * MAX_STRING_LENGTH);
				scanf("%s", towns[i].offices[j].packages[k].id);
				scanf("%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
	int queries;
	scanf("%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	while (queries--) {
		int type;
		scanf("%d", &type);
		switch (type) {
		case 1:
        {
			scanf("%s", town_name);
			town* t = find_town(towns, towns_count, town_name);
			print_all_packages(*t);
			break;
        }
		case 2:
        {
			scanf("%s", town_name);
			town* source = find_town(towns, towns_count, town_name);
			int source_index;
			scanf("%d", &source_index);
			scanf("%s", town_name);
			town* target = find_town(towns, towns_count, town_name);
			int target_index;
			scanf("%d", &target_index);
			send_all_acceptable_packages(source, source_index, target, target_index);
			break;
        }
		case 3:
        {
			printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
			break;
        }
		}
	}
	return 0;
}