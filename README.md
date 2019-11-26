# DeviceDriver
1. 개요
유저 프로그램에서 문자를 입력받아 
- 대소문자를 변환하여 저장한다. 
- 총 100개의 문자를 저장하고 100개가 넘는 입력에 대해서는 처음부터 Overwrite하는 메모리 디바이스 드라이버를 만든다. 
-유저 프로그램에서는 문자 Input만을 수행하고 위의 기능은 드라이버 프로그램에서 처리한다. 


2. 프로그램 구조 설명
2.1 함수에 관한 설명

-static int mydrv_open(struct inode* inode, struct file* file)
:노드를 열 때 수행한다. 이 항목이 NULL로 되어 있으면 디바이스 open 호출은 언제나 성공적이다.

-static int mydrv_release(struct inode* inode, struct file* file)
:노드를 닫을 때 수행된다.

-static ssize_t mydrv_read(struct file* file, char* buf, size_t count, loff_t* ppos):
:디바이스에서 데이터를 가져오기 위해서 사용한다. 여기에 NULL값을 사용하면 read시스템 		콜은 –EINVAL(“잘못된 매개변수”)값을 돌려 주며 실패한다. 음수 값이 아닌 리턴 값은 성공적		으로 읽은 바이트 수를 나타낸다.

-static ssize_t mydrv_write(struct file* file, const char* buf, size_t count, loff_t* ppos)
:디바이스에 데이터를 보낸다. NULL값을 쓰면 write시스템 콜에 대해서 –EINVAL을 돌려준다. 리턴 값이 음수가 아니면 성공적으로 작성된 데이터의 바이트 크기이다.

-int mydrv_init(void)
:케릭터 디바이스를 만드는 함수

-void mydrv_cleanup(void)
:모든 공간을 해제하는 함수

-int copy_to_user(void_user* to, const void* from, unsigned long n)
:from이 가리키는 주소의 커널 메모리 블록 데이터를 to가 가리키는 사용자 메모리 블록 데이터에 바이트 크기 단위인 n만큼 써넣는다. 이 함수는 써넣은 공간의 유효성 검사를 수행한다. 성공하면 0 이상의 값, 그렇지 않다면 0보다 작은 값을 반환한다.

-int copy_from_user(void* to, const void_user* from, unsigned long n)
:from이 가리키는 주소의 사용자 메모리 블록 데이터를 to가 가리키는 커널 메모리 블록 데이터에 바이트 크기 단위인 n만큼 써넣는다. 이 함수는 읽어올 공간의 유효성 검사를 수행한다. 성공하면 0 이상의 값 그렇지 않다면 0보다 작은 값을 반환한다.



2.2 다이어그램



3. 실행 결과
-성공한 결과


입력받은 문자 :  aaaaaaaaaaAAAAAAAAAAbbbbbbbbbbBBBBBBBBBBccccccccccCCCCCCCCCCddddddddddDDDDDDDDDDeeeeeeeeeeEEEEEEEEEEffffffffffFFFFFFFFFF
이렇게 총 120개의 문자를 입력받았는데, 100개까지인 E까지만 받고 f부터는 앞에서부터 덮어쓴다.
대소문자도 변환이 되었음을 알 수 있다.

-실패한 결과


입력받은 문자:
AAAAAAAAAAbbbbbbbbbbCCCCCCCCCCddddddddddEEEEEEEEEEffffffffffGGGGGGGGGGhhhhhhhhhhIIIIIIIIIIjjjjjjjjjjKKKKKKKKKK
대소문자 변환에 성공하고 덮어쓰는 것도 성공했지만 왜인지 B부터는 출력하지 않았다. 

4. 고찰
 메이크 파일을 할 때 자꾸 에러가 생겨서 메이크 파일을 다르게 바꿔보기도 했는데 에러는 사라지지 않아서 답답했다. 알고보니 메이크 파일명을 Makefile로 해야 하는데, makefile로 해서 그런 것이었다. 지금까지 대문자 쓰기가 귀찮아서 계속 makefile로 사용해도 별 이상이 없었는데, 이번에 그런 것을 보고 신기했다. 예전에 자료구조 수업을 들을 때 Makefile이라고 안하면 문제가 생길 수도 있다고 하셨던 교수님의 말씀이 이제야 떠올랐다. 그 에러 원인만 찾다가 2시간을 날렸다.. 앞으로는 귀찮더라도 규칙에 맞게 해야겠다고 뼈저리게 느꼈다.
 sudo 명령어를 터미널에서 한 번만 구현 가능하다는 것이 의문이었다. 코드를 고치고 다시 메이크를 하고 다시 sudo명령어를 치면 항상 에러가 났다. 그래서 그 때 마다 새로운 터미널을 열어서 했다. 이렇게 하니 너무 시간이 많이 걸렸다. 조금 편한 방법이 있었으면 좋겠다. 그리고 매번 명령어를 사용할 때마다 비밀번호를 쳐야 하는데 비밀번호를 치는 시간이 너무 짧아 실패한 적이 많았다. 처음에 비밀번호를 치는 3번의 기회를 다 날리고 나서 3번 다 틀렸다는 문구가 떴는데 문득 교수님이 컴퓨터 망가져도 모른다고 하셨던 말이 떠올라 겁났지만, 다행히도 컴퓨터가 망가진 것은 아니었다. 그리고 비밀번호를 올바르게 입력했음에도 잘못 입력했다는 문구가 떠서 정말 오랫동안 고민하고 시간을 날렸지만 버퍼문제에서 생기는 것 같아 무시하기로 했다.    
 처음에 100개까지만 받는 것을 구현하려고 했다. 그래서 mydrv_read와 mydrv_write에서 copy_to_user(), copy_to_from()의 매개변수에 count가 100보다 클 경우에는 100을 넣어 100까지만 데이터를 읽고 쓰도록 했더니 100까지 받는 것에 성공했다. 그러나 이렇게 하니 100넘는 부분을 저장해서 overwrite 하는 것을 구현하기가 어려웠다. 그래서 매개변수를 제한하지 않고 100 다음 부터는 null을 넣어 100까지 제한하도록 했다. 
 이제 덮어쓰는 부분을 구현하려고 하니 문제가 또 생겼다. 100보다 클 때 넘는 부분을 0부터 넘는 수만큼 덮어 쓰고 그 다음 수 부터는 정상적으로 받도록 하였다. 그러나 덮어쓰는 부분까지는 성공하였지만 왜인지 그 다음 수부터 출력하지를 않았다. 그래서 다른 방법을 생각해 보았다. 이 코드는 200이 넘었을 때 문제가 생길 수 있어서 그 부분도 개선하여 바꾸었다. 결국 성공 하였지만, 이전 코드가 가독성이 좋았는데 원인을 알 수 없어 아쉬웠다. 
 디바이스 드라이버라는 것을 처음 코딩해 보았는데 너무 어려웠다. 이론만 알다가 코드로 보려고 하니 너무 어려웠다... 예제 코드를 이해하기 위해 하나하나 인터넷에 찾아서 공부했지만 아직 완전히 이해가 되지 않아 아쉬웠다. 그래도 항상 유저 모드에서 코딩하다가 커널 모드에서 하니 새로운 세계를 경험한 느낌이었다. 그리고 이렇게 커널 모드에서 코딩하는 사람들은 정말 대단하다고 느꼈고 나는 정말 코딩과 적성이 안 맞는 사람이라는 것을 이번에 새로 깨달았다. 앞으로 전자기기를 사용할 때마다 이런 os를 만드는 사람들의 위대함을 뼛속까지 느끼면서 사용해야겠다. 새삼 조교님과 교수님은 정말 대단하시다고 느꼈다.

5. 프로그램 소스 파일
<mydrv.c>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "mydrv"
#define MYDRV_MAX_LENGTH	4096
#define MIN(a,b)	(((a)<(b)) ? (a) : (b))

struct class* myclass;
struct cdev* mycdev;
struct device* mydevice;
static char* mydrv_data;
static int mydrv_read_offset, mydrv_write_offset;
dev_t mydev;
MODULE_LICENSE("GPL");

static int mydrv_open(struct inode* inode, struct file* file){//노드를 열 때 수행
	return 0;	
}

static int mydrv_release(struct inode* inode, struct file* file){//노드를 닫을 때 수행
	return 0;	
}

static ssize_t mydrv_read(struct file* file, char* buf, size_t count, loff_t* ppos){
	int i = 0;
	int j, tst;

	if((buf==NULL||(count<0))) //넘어 온 값이 없는 경우
		return -EINVAL;

	if(count + mydrv_write_offset >= MYDRV_MAX_LENGTH){ //길이가 있는 지 없는 지 확인
		return 0;
	}

	if(copy_to_user(buf, mydrv_data + mydrv_read_offset, count)) //user에서 넘어온 변수의 주소 값에 값을 담는다
		return -1;
	
	for(tst = count ; tst > 0 ; tst -=100){ //덮어쓰는 부분, 100단위로 잘라 계속 덮어쓴다 
		for(j = 0 ; j < 100 ; ++j){//j는 0에서 100사이에서만 변한다
			if(buf[i] >= 'A' && buf[i] <= 'Z') //대문자일 경우
				buf[j] = buf[i] + 32; //소문자로 바꾸고
			else if(buf[i] >= 'a' && buf[i] <= 'z') //소문자일 경우
				buf[j] = buf[i] - 32; //대문자로 바꾼다
			//buf의 끝까지 도달하면 null이므로 더 이상 읽어오지 않는다.
			i++;//i는 계속 증가한다
		}
	}

	for(i = 100 ; i < count ; i++) //100 이후부터는 널값을 넣는다
		buf[i] = '\0';
	
	mydrv_write_offset += count;
	return count;//성공했으면 
}

static ssize_t mydrv_write(struct file* file, char* buf, size_t count, loff_t* ppos){
	//user에서 넘어온 변수의 주소 값에 있는 값을 디바이스에 보낸다
	if( copy_from_user(mydrv_data + mydrv_write_offset, buf, count))
 		return -1;

	mydrv_read_offset += count;
	return count; //성공했다면 쓴 바이트 수를 반환
}

struct file_operations mydrv_fops={
	.owner = THIS_MODULE,
	.read = mydrv_read,
	.write = mydrv_write,
	.open = mydrv_open,
	.release = mydrv_release
};

int mydrv_init(void){
	if( alloc_chrdev_region(&mydev, 0, 1, DEVICE_NAME) < 0 ) //캐릭터 디바이스 영역을 말록
		return –EBUSY; //실패하면 –EBUSY 반환
	
	myclass = class_create(THIS_MODULE, "mycharclass"); //class구조체(모듈에 대한 모든 정보를 담고 있음) 생성
	
	if( IS_ERR(myclass) ){ //에서 판단
		unregister_chrdev_region(mydev, 1); //영역 잡은 부분 해제
		return PTR_ERR(myclass); //에러가 발생했음을 알림
	}
	
	mydevice = device_create(myclass, NULL, mydev, NULL, "mydevicefile"); //디바이스 구조체 생성
	if( IS_ERR(mydevice) ){
		class_destroy(myclass);
		unregister_chrdev_region(mydev, 1);
		return PTR_ERR(mydevice);
	}
	
	mycdev = cdev_alloc(); //케릭터 디바이스 크기만큼 공간 할당
	mycdev->ops = &mydrv_fops; //파일연산자
	mycdev->owner = THIS_MODULE; //자기자신이 권한을 할당
	
	if( cdev_add(mycdev, mydev, 1) <0 ){//추가적으로 공간을 더함
		device_destroy(myclass, mydev);
		class_destroy(myclass);
		unregister_chrdev_region(mydev, 1);
		return -EBUSY;
	}
	
	mydrv_data = (char*)kmalloc(MYDRV_MAX_LENGTH * sizeof(char), GFP_KERNEL);
	mydrv_read_offset = mydrv_write_offset = 0;
	return 0;
}

void mydrv_cleanup(void){//모든 공간 해제
	kfree(mydrv_data);
	cdev_del(mycdev);
	device_destroy(myclass, mydev);
	class_destroy(myclass);
	unregister_chrdev_region(mydev, 1);
}

module_init(mydrv_init); //모듈이 등록될 때 호춯
module_exit(mydrv_cleanup); //모듈이 삭제될 때 호출

MODULE_LICENSE("GPL");

<failure.c>//실패한 코드
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "mydrv"
#define MYDRV_MAX_LENGTH	4096
#define MIN(a,b)	(((a)<(b)) ? (a) : (b))

struct class* myclass;
struct cdev* mycdev;
struct device* mydevice;
static char* mydrv_data;
static int mydrv_read_offset, mydrv_write_offset;
dev_t mydev;
MODULE_LICENSE("GPL");

static int mydrv_open(struct inode* inode, struct file* file){
	return 0;	
}

static int mydrv_release(struct inode* inode, struct file* file){
	return 0;	
}

static ssize_t mydrv_read(struct file* file, char* buf, size_t count, loff_t* ppos){
	int i;

	if((buf==NULL||(count<0)))
		return -EINVAL;

	if(count + mydrv_write_offset >= MYDRV_MAX_LENGTH){
		return 0;
	}

	if(copy_to_user(buf, mydrv_data + mydrv_read_offset, count))
		return -1;
//이전 코드와 다른부분	
	if(count < 100){//100보다 작을 때는 문제가 없으므로 정상적으로 수행
		for(i = 0 ; i < count ; ++i){
			if(buf[i] >= 'A' && buf[i] <= 'Z')
				buf[i] += 32;
			else if(buf[i] >= 'a' && buf[i] <= 'z')
				buf[i] -= 32;
		}
	 }else{//100보다 큰 경우
		for(i = 0 ; i < 100 ; ++i){
			if(i < count – 100){//i가 buf가 100초과한 수보다 작을 때 buf의 100보다 넘은 부분을 덮어쓴다
				if(buf[100 + i] >= 'A' && buf[100 + i] <= 'Z')
					buf[i] = buf[100 + i] + 32;
				else if(buf[100 + i] >= 'a' && buf[100 + i] <= 'z')
					buf[i] = buf[100 + i] - 32;
				else
					buf[i] = buf[100 + i];
			}else{//i가 100보다 넘은 수 보다 큰 경우 이곳으로 들어온다. 이 때는 덮어 쓸 필요가 없다
				if(buf[i] >= 'A' && buf[i] <= 'Z')
					buf[i] += 32;
				else if(buf[i] >= 'a' && buf[i] <= 'z')
					buf[i] -= 32;
			}
		}

		for(i = 100 ; i < count ; i++)
			buf[i] = NULL;
	}

	mydrv_write_offset += count;
	return count;
}

static ssize_t mydrv_write(struct file* file, char* buf, size_t count, loff_t* ppos){

	if( copy_from_user(mydrv_data + mydrv_write_offset, buf, count))
 		return -1;

	mydrv_write_offset += count;
	return count;
}

struct file_operations mydrv_fops={
	.owner = THIS_MODULE,
	.read = mydrv_read,
	.write = mydrv_write,
	.open = mydrv_open,
	.release = mydrv_release
};

int mydrv_init(void){
	if( alloc_chrdev_region(&mydev, 0, 1, DEVICE_NAME) < 0 )
		return -EBUSY;
	
	myclass = class_create(THIS_MODULE, "mycharclass");
	
	if( IS_ERR(myclass) ){
		unregister_chrdev_region(mydev, 1);
		return PTR_ERR(myclass);
	}
	
	mydevice = device_create(myclass, NULL, mydev, NULL, "mydevicefile");
	if( IS_ERR(mydevice) ){
		class_destroy(myclass);
		unregister_chrdev_region(mydev, 1);
		return PTR_ERR(mydevice);
	}
	
	mycdev = cdev_alloc();
	mycdev->ops = &mydrv_fops;
	mycdev->owner = THIS_MODULE;
	
	if( cdev_add(mycdev, mydev, 1) <0 ){
		device_destroy(myclass, mydev);
		class_destroy(myclass);
		unregister_chrdev_region(mydev, 1);
		return -EBUSY;
	}
	
	mydrv_data = (char*)kmalloc(MYDRV_MAX_LENGTH * sizeof(char), GFP_KERNEL);
	mydrv_read_offset = mydrv_write_offset = 0;
	return 0;
}

void mydrv_cleanup(void){
	kfree(mydrv_data);
	cdev_del(mycdev);
	device_destroy(myclass, mydev);
	class_destroy(myclass);
	unregister_chrdev_region(mydev, 1);
}

module_init(mydrv_init);
module_exit(mydrv_cleanup);

MODULE_LICENSE("GPL");

<test_app.c>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define MAX_SIZE  200
int main(void){
  	int fd;
  
  	char* in = (char*)malloc(sizeof(char) * MAX_SIZE);
  	char* out = (char*)malloc(sizeof(char) * MAX_SIZE);
   	if( (fd=open("/dev/mydevicefile", O_RDWR))<0 ){//파일을 생성, 읽고 쓸 수 있는 모드
	  	perror("open error");//실패 시
  		return -1;
  	}
  	strcpy(out, "aaaaaaaaaaAAAAAAAAAAbbbbbbbbbbBBBBBBBBBBccccccccccCCCCCCCCCCddddddddddDDDDDDDDDDeeeeeeeeeeEEEEEEEEEEffffffffffFFFFFFFFFF");
  	write(fd, out, MAX_SIZE); //파일에 문자를 쓴다
  
  	read(fd, in, MAX_SIZE); //파일에 있는 값을 읽어온다
	printf("%s \n", in);
  
  	free(in);
  	free(out);
  	close(fd);
  	
	return 0;
}

6. 자료 출처
http://naver.me/I5lOTOm8, http://me2.do/5RTZ0Ys6 
