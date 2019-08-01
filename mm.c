#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include <sys/time.h>
#include <pthread.h>
#define FIRST_INPUT_FILE_NAME "data5M-1"
#define SECOND_INPUT_FILE_NAME "data5M-2"
#define THIRD_INPUT_FILE_NAME "data50M-1"
#define FOURTH_INPUT_FILE_NAME "data50M-2"


#define FIRST_RESULT "result_5M-1"
#define SECOND_RESULT "result_5M-2"
#define THIRD_RESULT "result_50M-1"
#define FOURTH_RESULT "result_50M-2"
#define EACH_VALUE_MAX_LENGTH 11
#define HOW_MANY_VALUES_IN_A_ROW 5
#define TIME_CHECK_LIMIT_VALUE 1000000.0
#define LINE_LENGTH ((EACH_VALUE_MAX_LENGTH + sizeof(char))*HOW_MANY_VALUES_IN_A_ROW + sizeof(char))
#define ERROR_EXIT(A) {printf(A);exit(1);}
#define DEBUG_GOT_WELL 1   //배열이 제대로 정렬됐는지, 또, 저장된 파일이 제대로 정렬된 파일인지 검사하는 옵션
#define DEBUG_HOW_MANY_ELEMENTS 1   //얼마나 많은 값들이 파일에 저장되어있는지 검사하는 옵션
#define DEBUG_FILE_LOAD_SPEED_TEST 0   //파일 적재에 얼마나 시간이 걸리는지 검사하는 옵션
#define DEBUG_FILE_SAVE_SPEED_TEST 0   //파일 저장에 얼마나 시간이 걸리는지 검사하는 옵션
#define THREADS_ERUPTION 2

typedef long bt; //basic type
typedef struct merge_need {
	bt * values_array;
	int from;
	int to;
	int left_to_eruption; //쓰레드를 생성할 수 있는 일종의 텔로미어
}merge_need;
enum time_check_control { measure_start = 1, return_time = 2, peek_time = 3 };


int need_to_know_the_number_of_values(FILE * fp);   //파일 내의 숫자가 몇 개인지?
int translate_string_to_value(bt* values_array, FILE * fp, const int the_number_of_values); //파일 내의 숫자를 정수 배열로 저장
void print_values(const bt* const values_array, const int size);   //배열 내용을 출력 (권장X)
void store_values(const bt * const values_array, const int size, FILE * fp);   //배열 내용을 파일로 저장
void sort_each_file(const char * input_file_name, const char * output_file_name);   //각각의 파일들(250K, 1M)에 대해 정렬을 실시한다.
int was_this_sorted_properly(const bt * const values_array, const int size);   //배열이 제대로 정렬됐는지 확인한다.
int result_file_check(const char * const output_file_name);//결과 파일이 제대로 정렬됐는지 확인한다.
void* wanna_merge(void *total);
void merge(bt * const values_array, int array_1_start, const int array_1_end, const int array_2_end);
void sort(bt * values_array, const int size);   //정렬에 대한 추상함수
double timechecker(int control);   //시간 측정 함수

void sort(bt * values_array, const int size)
{
	pthread_t threads[2];
	int threads_id[2];

	merge_need total[2] = {
		{ values_array , 0, size >> 1, THREADS_ERUPTION },
	{ values_array , (size >> 1) + 1,size - 1, THREADS_ERUPTION }
	};
	for (int i = 0; i < 2; i++)
	{
		total[i].values_array = values_array;

		pthread_create(&threads[i], NULL, (void*)wanna_merge, (void*)&total[i]);
		if (threads_id[i] < 0)
		{
			perror("thread create error:");
			exit(0);
		}
	}
	for (int i = 0; i < 2; i++)
		pthread_join(threads[i], NULL);
	merge(values_array, 0, size >> 1, size - 1);
}
int main(void)
{
	printf("%s %s compiled by kitty.\n", __DATE__, __TIME__);
	printf("\n");
	sort_each_file(FIRST_INPUT_FILE_NAME, FIRST_RESULT);
	sort_each_file(SECOND_INPUT_FILE_NAME, SECOND_RESULT);
	sort_each_file(THIRD_INPUT_FILE_NAME, THIRD_RESULT);
	sort_each_file(FOURTH_INPUT_FILE_NAME, FOURTH_RESULT);
	printf("\n");
}

void *wanna_merge(void *total)
{
	register merge_need * now = (merge_need*)total;
	if (now->from == now->to)
		return NULL;
	merge_need m[2] =
	{
		{ now->values_array, now->from, (now->from + now->to) >> 1, 0 },
	{ now->values_array,((now->from + now->to) >> 1) + 1,now->to, 0 }
	};
	if (now->left_to_eruption > 0)   //쓰레드를 생성하는 경우와 아닌 경우는 나뉘어야함
	{
		m[0].left_to_eruption = m[1].left_to_eruption = now->left_to_eruption - 1;
		pthread_t threads[2];
		int threads_id[2];
		for (int i = 0; i < 2; i++)
		{
			pthread_create(&threads[i], NULL, (void*)wanna_merge, (void*)&m[i]);
			if (threads_id[i] < 0)
			{
				perror("thread create error:");
				exit(0);
			}
		}
		pthread_join(threads[0], NULL);
		pthread_join(threads[1], NULL);
	}
	else
	{
		wanna_merge(&m[0]);
		wanna_merge(&m[1]);
	}
	merge(now->values_array, now->from, (now->from + now->to) >> 1, now->to);
	return NULL;
}
void merge(bt * const values_array, int array_1_start, const int array_1_end, const int array_2_end)
{   ///Q. 변수를 만들고 대입하는 연산과 산술연산자 중 어떤게 더 빠를까? 그리고 동적 할당은?
	register int arr_1_index = array_1_start;
	register int arr_2_index = array_1_end + 1;
	int now_how_size_needed = array_2_end - array_1_start + 1;
	register bt * temp_array = (bt *)malloc(sizeof(bt)*(now_how_size_needed));
	register int i = 0;
	while (arr_1_index <= array_1_end && arr_2_index <= array_2_end)
	{
		if (values_array[arr_1_index] < values_array[arr_2_index])
			temp_array[i++] = values_array[arr_1_index++];
		else
			temp_array[i++] = values_array[arr_2_index++];
	}
	while (arr_1_index <= array_1_end)
		temp_array[i++] = values_array[arr_1_index++];
	while (arr_2_index <= array_2_end)
		temp_array[i++] = values_array[arr_2_index++];
	i = 0;
	while (i < now_how_size_needed)   //임시로 만든 배열에 정렬하였으므로 이걸 다시 values_array 배열에 넣는다.
		values_array[array_1_start++] = temp_array[i++];
	free(temp_array);
}
int need_to_know_the_number_of_values(FILE * fp)
{   //우선 동적할당 하기 전에 파일이 몇 개의 정수를 포함하는지 알아낸다. 조건 : 한 줄에 5개
	///Q.처리하기 전에, 처리해야 할 데이터의 갯수를 아는 것은 중요한가?
	char temp[LINE_LENGTH];
	int count = 0;
	while (fgets(temp, sizeof(temp), fp))
		count++;
	fseek(fp, 0, SEEK_SET);      //file seeker initializing to zero is required.
	return count * HOW_MANY_VALUES_IN_A_ROW;
}
int translate_string_to_value(bt* values_array, FILE * fp, const int the_number_of_values)
{   //파일의 한 행씩 떼어와 문자열을 정수로 바꿔 저장하는 함수 
	int processed_count = 0;
	char each_line[LINE_LENGTH];
	char buffer_to_make_value_from_string[EACH_VALUE_MAX_LENGTH] = { 0 };
	int buffer_index = 0;
	while (fgets(each_line, sizeof(each_line), fp)) {   //파일에서 한 행 씩 떼내고 
		{
			{
				{
					int value_per_line = 0;
					for (int i = 0; i < LINE_LENGTH; i++)   //각 행을 검사
					{   ///Q. 너무 많은 변수를 인자로 넘겨야한다면 구조체로 묶어야하나 아니면 함수로 만들지 말아야하나?
						buffer_to_make_value_from_string[buffer_index] = each_line[i];
						if (each_line[i] >= '0' && each_line[i] <= '9')
						{
							buffer_index++;
							if (buffer_index >= EACH_VALUE_MAX_LENGTH)
								ERROR_EXIT("FILE PARSING ERROR! each value length in file was overruned.\n");
							continue;
						}
						else if (each_line[i] == '\n' || each_line[i] == ' ')
							if (buffer_index != 0)   //숫자를 입력받다가 다른 문자가 나오면 버퍼를 정수로 바꿔 저장한다.
							{
								buffer_to_make_value_from_string[buffer_index] = NULL;
								values_array[processed_count++] = atoi(buffer_to_make_value_from_string);
								buffer_index = 0;
								value_per_line++;
								if (value_per_line >= HOW_MANY_VALUES_IN_A_ROW)
									break;
							}
					}
				}
			}
		}
	}
	return processed_count;
}
void print_values(const bt* const values_array, const int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%10d ", values_array[i]);
		if ((i + 1) % HOW_MANY_VALUES_IN_A_ROW == 0)
			printf("\n");
	}
}
void store_values(const bt * const values_array, const int size, FILE * fp)
{
	for (int i = 0; i < size; i += HOW_MANY_VALUES_IN_A_ROW)
	{
		for (int j = 0; j < HOW_MANY_VALUES_IN_A_ROW; j++)
			fprintf(fp, "%10d ", values_array[i + j]);
		fprintf(fp, "\n");
	}
}

int was_this_sorted_properly(const bt * const values_array, const int size)
{
	for (int i = 0; i < size - 1; i++)
		if (values_array[i] > values_array[i + 1])
			return 0;
	return 1;
}
int result_file_check(const char * const output_file_name)
{
	FILE * fp = fopen(output_file_name, "rt");
	bt * values_array;
	int the_number_of_values;
	if (fp == NULL)
		ERROR_EXIT("I CAN'T READ THAT FILE!\n");
	the_number_of_values = need_to_know_the_number_of_values(fp);
	values_array = (bt *)malloc(sizeof(bt)*the_number_of_values);
	if (the_number_of_values != translate_string_to_value(values_array, fp, the_number_of_values))
		ERROR_EXIT("FILE PARSING ERROR! is something wrong at file or source code macro setting?\n");
	//두가지 방식으로 숫자 갯수를 셌을 때, 다르면 파일이나 코드 설정이 잘못된 것.
	fclose(fp);
#if DEBUG_HOW_MANY_ELEMENTS
	printf("\tlast test said file has %d values.\n", the_number_of_values);
#endif 
	if (was_this_sorted_properly(values_array, the_number_of_values))
		return 1;
	return 0;
}
void sort_each_file(const char * input_file_name, const char * output_file_name)
{
	bt * values_array;   //★실제 파일로부터 읽은 값들을 저장하는 배열★//
	int the_number_of_values;
	//////////////
	//*파일 입력*//
#if DEBUG_FILE_SAVE_SPEED_TEST
	timechecker(measure_start);
#endif
	{
		FILE * fp = fopen(input_file_name, "rt");
		if (fp == NULL)
		{
			printf("no such [%s] file in this directory.\n", input_file_name);
			return;
		}
		the_number_of_values = need_to_know_the_number_of_values(fp);
		values_array = (bt *)malloc(sizeof(bt)*the_number_of_values);
		if (the_number_of_values != translate_string_to_value(values_array, fp, the_number_of_values))
			ERROR_EXIT("FILE PARSING ERROR! is something wrong at file or source code macro setting?\n");
		//두가지 방식으로 숫자 갯수를 셌을 때, 다르면 파일이나 코드 설정이 잘못된 것.
		fclose(fp);
	}
#if DEBUG_HOW_MANY_ELEMENTS
	printf("\n\t%d values will be sorted.\n", the_number_of_values);
#endif
#if DEBUG_FILE_SAVE_SPEED_TEST
	printf("\tvalues loaded from file in %f seconds.\n", timechecker(return_time));
#endif
	//*정렬*//
	timechecker(measure_start);
	sort(values_array, the_number_of_values);
	printf("[%f] seconds was taken to sort.\n", timechecker(return_time));
#if DEBUG_GOT_WELL
	if (was_this_sorted_properly(values_array, the_number_of_values))
		printf("\tvalues parsed from file correctly.\n");
	else
		printf("\tvalues parsed from file INCORRECTLY.\n");
#endif
	//*파일 출력*//
#if DEBUG_FILE_SAVE_SPEED_TEST
	timechecker(measure_start);
#endif
	{
		FILE * fp = fopen(output_file_name, "wt");
		if (fp == NULL)
			ERROR_EXIT("I CAN'T WRITE FILE!\n");
		store_values(values_array, the_number_of_values, fp);
		fclose(fp);
	}
#if DEBUG_FILE_SAVE_SPEED_TEST
	printf("\tfile saved in %f seconds.\n", timechecker(return_time));
#endif
#if DEBUG_GOT_WELL
	if (result_file_check(output_file_name))
		printf("\tvalues saved in file correctly.\n");
	else
		printf("\tvalues saved in file INCORRECTLY.\n");
#endif
	printf("\n");
	//////////////
	free(values_array);
}
double timechecker(int control)
{
	static struct timeval start_time;
	static struct timeval end_time;
	static double start_time2;
	static double end_time2;
	switch (control)
	{
	case measure_start:
		gettimeofday(&start_time, NULL);
		start_time2 = (double)start_time.tv_sec + ((double)start_time.tv_usec / TIME_CHECK_LIMIT_VALUE);
		break;
	case return_time:
		gettimeofday(&end_time, NULL);
		end_time2 = (double)end_time.tv_sec + ((double)end_time.tv_usec / TIME_CHECK_LIMIT_VALUE);
		return end_time2 - start_time2;
	case peek_time:
		return end_time2 - start_time2;
	default:
		printf("Improper Time Control Trial.\n");
		exit(1);
	}
	return -1.0;
}
