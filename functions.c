#include <stdlib.h>
#include <stdio.h>

#define n_sector 3

/* Fill in the functions and define helper functions if you need to */

float*** create_sector_times(unsigned int* n_drivers, unsigned int* n_laps){
    float ***data;
    int i,j,k;
    scanf("%u %u",n_drivers,n_laps);
    data=(float***)malloc((*n_drivers)*sizeof(float**));
    for (i=0;i<*n_drivers;i++){
        data[i]=(float**)malloc((*n_laps)*sizeof(float*));
        for (j=0;j<*n_laps;j++){
            data[i][j]=(float*)malloc(n_sector*sizeof(float));
        }
    }
    for (i=0;i<*n_drivers;i++){
        for (j=0;j<*n_laps;j++){
            for(k=0;k<n_sector;k++){
                scanf("%f",&data[i][j][k]);
            }   
        }
    }
    return data;
}


unsigned int** create_positions(unsigned int* p_drivers, unsigned int* n_races){
    unsigned int **data;
    int i,j;
    scanf("%u %u",p_drivers,n_races);
    data=(unsigned int**)malloc((*p_drivers)*sizeof(unsigned int*));
    for (i=0;i<*p_drivers;i++){
        data[i]=(unsigned int*)malloc((*n_races)*sizeof(unsigned int));
    }
    for (i=0;i<*p_drivers;i++){
        for(j=0;j<*n_races;j++){
            scanf("%u",&data[i][j]);
        }
    }
    return data;
}


float** calculate_lap_times(float*** sector_times, unsigned int n_drivers, unsigned int n_laps){
    float** data;
    float sum;
    int i,j,k;
    sum=0;
    data=(float**)malloc((n_drivers)*sizeof(float*));
    for (i=0;i<n_drivers;i++){
        data[i]=(float*)malloc((n_laps)*sizeof(float));
    }
    for (i=0;i<n_drivers;i++){
        for(j=0;j<n_laps;j++){
            for (k=0;k<n_sector;k++){
                sum += sector_times[i][j][k];
            }
            data[i][j]=sum;
            sum=0;
        }
    }
    return data;
}


unsigned int find_fastest_lap(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    int i,j,e;
    unsigned int driver;
    float time;
    driver=0;
    e=0.0001;
    time=lap_times[0][0];
    for (i=0;i<n_drivers;i++){
        for (j=0;j<n_laps;j++){
           if (time-lap_times[i][j]>e){
               driver=i;
               time=lap_times[i][j];
           } 
        }
    }
    return driver;
}


unsigned int find_driver_fastest_lap(float** sector_times_of_driver, unsigned int n_laps){
    int m,n,e;
    unsigned int lap;
    float time2,sum;
    sum=0;
    lap=0;
    time2=0;
    e=0.0001;
    for (m=0;m<n_laps;m++){
        for (n=0;n<n_sector;n++){
            sum+=sector_times_of_driver[m][n];
        }
        if (time2==0){
            time2=sum;
        }
        if (time2-sum>e){
            lap=m;
            time2=sum;
        }
        sum=0;
    }
    return lap;
}


float* selection_sort(float* arr, unsigned int len, char ord){
    int i,count,var_index;
    float var;
    float* sorted_arr;
    sorted_arr=(float*)malloc(len*sizeof(float));
    for (i=0;i<len;i++){
        sorted_arr[i]=arr[i];
    }
    var=sorted_arr[0];
    var_index=0;
    count=0;
    if (ord=='A'){
        while (count<len){
            for (i=count;i<len;i++){
                if (sorted_arr[i]<var){
                    var=sorted_arr[i];
                    var_index=i;
                }
            }
            sorted_arr[var_index]=sorted_arr[count];
            sorted_arr[count]=var;
            var=sorted_arr[count+1];
            var_index=count+1;
            count++;
        }
    }
    if (ord=='D'){
        while (count<len){
            for (i=count;i<len;i++){
                if (sorted_arr[i]>var){
                    var=sorted_arr[i];
                    var_index=i;
                }
            }
            sorted_arr[var_index]=sorted_arr[count];
            sorted_arr[count]=var;
            var=sorted_arr[count+1];
            var_index=count+1;
            count++;
        }
    }
    return sorted_arr;
}
unsigned int* selection_sort_helper(float* arr, unsigned int len){
    int i,j,count,var_index,count_index;
    float var;
    float* sorted_arr;
    unsigned int* index_order;
    sorted_arr=(float*)malloc(len*sizeof(float));
    for (i=0;i<len;i++){
        sorted_arr[i]=arr[i];
    }
    index_order=(unsigned int*)malloc(len*sizeof(unsigned int));
    var=sorted_arr[0];
    var_index=0;
    count=0;
    for (j=0;j<len;j++){
        index_order[j]=j;
    }
    while (count<len){
        for (i=count;i<len;i++){
            if (sorted_arr[i]<var){
                var=sorted_arr[i];
                var_index=i;
            }
        }
        sorted_arr[var_index]=sorted_arr[count];
        sorted_arr[count]=var;
        count_index=index_order[count];
        index_order[count]=index_order[var_index];
        index_order[var_index]=count_index;
        var=sorted_arr[count+1];
        var_index=count+1;
        count++;
        }
    return index_order;
}

unsigned int* find_finishing_positions(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    float sum;
    float* finish_time;
    int i,j;
    sum=0;
    finish_time=(float*)malloc(n_drivers*sizeof(float));
    for (i=0;i<n_drivers;i++){
        for (j=0;j<n_laps;j++){
            sum+=lap_times[i][j];
        }
        finish_time[i]=sum;
        sum=0;
    }
    return selection_sort_helper(finish_time,n_drivers);
}


float* find_time_diff(float** lap_times, unsigned int n_drivers, unsigned int n_laps, unsigned int driver1,
    unsigned int driver2){
        float* diff_array;
        int i;
        diff_array=(float*)malloc(n_laps*sizeof(float));
        for (i=0;i<n_laps;i++){
            if (i>0){
                diff_array[i]=diff_array[i-1]+lap_times[driver1][i]-lap_times[driver2][i];
            }
            else {
                diff_array[i]=lap_times[driver1][i]-lap_times[driver2][i];
            }
        }
    return diff_array;
}


unsigned int* calculate_total_points(unsigned int** positions, unsigned int p_drivers, unsigned int n_races){
    unsigned int* points;
    unsigned int* mapping;
    int i,j,k;
    mapping=(unsigned int*)malloc(p_drivers*sizeof(unsigned int));
    for (k=0;k<p_drivers;k++){
        scanf("%u",&mapping[k]);
    }
    points=(unsigned int*)calloc(p_drivers,sizeof(unsigned int));
    for (i=0;i<p_drivers;i++){
        for (j=0;j<n_races;j++){
            points[i]+=mapping[positions[i][j]-1];
        }
    }
    return points;
}
unsigned int* selection_sort_helper_int(unsigned int* arr, unsigned int len){
    int i,j,count,var_index,count_index;
    unsigned int var;
    unsigned int* sorted_arr;
    unsigned int* index_order;
    sorted_arr=(unsigned int*)malloc(len*sizeof(unsigned int));
    for (i=0;i<len;i++){
        sorted_arr[i]=arr[i];
    }
    index_order=(unsigned int*)malloc(len*sizeof(unsigned int));
    var=sorted_arr[0];
    var_index=0;
    count=0;
    count_index=0;
    for (j=0;j<len;j++){
        index_order[j]=j;
    }
    while (count<len){
        for (i=count;i<len;i++){
            if (sorted_arr[i]>var){
                var=sorted_arr[i];
                var_index=i;
            }
        }
        sorted_arr[var_index]=sorted_arr[count];
        sorted_arr[count]=var;
        count_index=index_order[count];
        index_order[count]=index_order[var_index];
        index_order[var_index]=count_index;
        var=sorted_arr[count+1];
        var_index=count+1;
        count++;
        }
    return index_order;
}
unsigned int find_season_ranking(unsigned int* total_points, unsigned int p_drivers, unsigned int id){
    unsigned int i;
    unsigned int* standings;
    standings=selection_sort_helper_int(total_points,p_drivers);
    for (i=0;i<p_drivers;i++){
        if (standings[i]==id){
            return i+1;
        }
    }
    return 0;
}
