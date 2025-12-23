#include "read_dir.h"

#include <time.h>

// function prototypes
void process_files(char *name);
void enqueue(char *name, que_t *q);
void dequeue(que_t *q);
void peek_front(char *name,que_t q);
bool queue_empty(que_t q);
void initq(que_t *q);

// main function
int main(int argc,char *argv[]) {

  if (2 != argc) {
    printf(" usage: %s dirpath\n", argv[0]);
    exit(-1);
  }
  else {
    //process directory
    process_files(argv[1]);       
  }
  
  return 0;
}

// traverse a directory tree applying a function when a file is found
void process_files(char *root)
{
  int num_files = 0;
  int num_REGfiles =0;
  int num_dir = 0;
  double average_size =0;
  int smallest_size = 0;
  int largest_size = 0;

  //allocate tm struct
  struct tm time;

  time_t most_recent_mod = 0;
  char most_recent_name[MAXLENGTH+1];
  time_t least_recent_mod = 0;
  char least_recent_name[MAXLENGTH+1];

  que_t nameq;
  char dname[MAXLENGTH+1];
  char cname[MAXLENGTH+1];
  char prefix[MAXLENGTH+1];

  struct dirent *dp;
  DIR *dirp;

  unsigned int fd;
  struct stat file_info;
  struct stat lfile_info;

  bool symbolic_link=false;

    initq(&nameq);
    enqueue(root,&nameq);

    while (true != queue_empty(nameq)) {
      peek_front(dname,nameq); 
      dequeue(&nameq);
      
      dirp = opendir(dname);
      if (dirp != NULL) { // it is a directory


    symbolic_link = false;
	printf("directory : %s\n",dname);
    //adds to directory count
    num_dir++;
	strncpy(prefix, dname, MAXLENGTH);
	strncat(prefix,"/", MAXLENGTH);
	
    //check if symbolic link
    if(lstat(dname, &lfile_info) == 0){
        if(S_ISLNK(lfile_info.st_mode)){
            printf("%s is symbolic link\n",dname);
            symbolic_link = true;
        }

    }

    if(!symbolic_link){
	for (dp = readdir(dirp); NULL != dp; dp = readdir(dirp)) {
	  if ((strcmp(dp->d_name,"..") != 0) && 
	      (strcmp(dp->d_name,".") != 0)) {
	    
	    // prevent from infinite loop
	    strncpy(cname, prefix, MAXLENGTH);
	    
	    // concatenate the prefix
	    strncat(cname, dp->d_name, MAXLENGTH);  
	    enqueue(cname,&nameq);
	  }
	}
    }
	closedir (dirp);
      } else { 
	printf(" processing file: %s\n", dname);
	//opens file
    fd = open(dname, O_RDONLY);
    if(-1 == fd){
        perror("Failed to open read only file");
        exit(-1);
    }
    //adds file to count
    num_files++;
    //gets file size
    if(fstat(fd, &file_info) == 0){

        //finds file most recently modified & least recently modified
        localtime_r(&(file_info.st_mtime), &time);
        time_t t = mktime(&time);
        if(t > most_recent_mod || least_recent_mod == 0){
           most_recent_mod = t;
           strncpy(most_recent_name, dname, MAXLENGTH);
        }

        if(t < least_recent_mod || least_recent_mod == 0){
            least_recent_mod = t;
            strncpy(least_recent_name, dname,MAXLENGTH);
        }

        //adds to average
        average_size = file_info.st_size + average_size;

        //checks if smallest size
        if( (int)file_info.st_size < smallest_size || smallest_size ==0){
            smallest_size = (int)file_info.st_size;
        }

        //checks if largest size
        if( (int)file_info.st_size > largest_size || largest_size == 0){
            largest_size = (int)file_info.st_size;
        }

        //checks if file is regular file
        if( S_ISREG(file_info.st_mode)){
            num_REGfiles++;
        }

    }
    close(fd);
      }      
    } // while


    printf("Smallest file size: %d bytes\n",smallest_size);
    printf("Largest file size: %d bytes\n",largest_size);
    printf("Number of directories: %d\n",num_dir);
    printf("Number of regular files: %d\n",num_REGfiles);
    printf("Most recently modified: %s\n", most_recent_name);
    printf("Least recently modified: %s\n", least_recent_name);


}

// initialize queue data structure
void initq(que_t *q) {
  q->head = q->tail = NULL;
}

// test whether queue data structure is empty
bool queue_empty(que_t q) {
  if (NULL == q.head) {
     return true;
  } else {
    return false;
  }
}

// add an element to queue
void enqueue(char *name, que_t *q) {
  item_t *temp;
  
  temp = (item_t *)malloc(sizeof(item_t));
  strncpy(temp->name,name,MAXLENGTH);
  temp->next = NULL;
  
  if (true == queue_empty(*q)) {
    q->head = temp;
    q->tail = temp;
  } else {
    q->tail->next = temp;
    q->tail = q->tail->next;
  }
}

// remove an element from the front of the queue
void dequeue(que_t *q) {
  item_t *temp;
  
  if (true == queue_empty(*q)) {
    printf(" error in dequeue \n");
    exit(-1);
  } else {
    temp = q->head;
    q->head = q->head->next;
    free(temp);
  }
}

// find element at front of queue without removing
void peek_front(char *name, que_t q) {
  if (true == queue_empty(q)) {
    printf(" error in dequeue \n");
     exit(-1);
  } else {
    strncpy(name, q.head->name, MAXLENGTH);
  }
} 
