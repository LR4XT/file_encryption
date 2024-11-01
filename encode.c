 //有开必有关
#define _CRT_SECURE_NO_WARNINGS
#include "common.h"

//关于需求，需要一个window 一个背景

SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;
SDL_Surface* surface_background = NULL;
SDL_Texture* textrue_background = NULL;
SDL_Event event ;
Button button[10];



void Load_Surface();
void PreparaeAll();
void Quit();
void button1Clicked();
void button2Clicked();
void button3Clicked();
void button4Clicked();
void button5Clicked();
void button6Clicked();
void button7Clicked();
void button8Clicked();
void button9Clicked();
void button10Clicked();
void lock1(const char* path, const int key);
void ulock1(const char* path, const int key);
void lock2(const char* path, const int key);
void ulock2(const char* path, const int key);
void lock3(const char* path, const char* key);
void ulock3(const char* path, const char* key);
void lock4(const char* path, const char* key);
void ulock4(const char* path, const char* key);
void clear_input_buffer();
char selectedFilePath[260];//全局变量存放函数内的文件路径
int main(int argc, char* argv[]) {//main用于存放主程序
	bool buttonHovered = false;
    char* path;
	
	PreparaeAll();
	int mouseX, mouseY;

	//SDL_RenderPresent(Renderer);

	//SDL_Delay(2000);
	while (1) {
		
		SDL_GetMouseState(&mouseX, &mouseY);//获取鼠标状态
		while (SDL_PollEvent(&event))//sdl_event等待事件
		{
			if (event.type == SDL_QUIT) {
				Quit();
				return 0;
			}

			else if (event.type == SDL_MOUSEBUTTONDOWN) {
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);

				// 检查鼠标按下状态
				for (int i = 0; i < 10; i++) {
					if (isMouseOverButton(&button[i], mouseX, mouseY)) {
						button[i].state = BUTTON_PRESSED;
					}
				}
			}
			else if (event.type == SDL_MOUSEBUTTONUP) {
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);

				// 检查鼠标释放状态
				for (int i = 0; i < 10; i++) {
					if (isMouseOverButton(&button[i], mouseX, mouseY)) {
						if (button[i].callback) {
							button[i].callback();
						}
						//添加相对应的执行函数
					
						//printf("Button %d clicked!\n", i + 1);
					}
					button[i].state = BUTTON_NORMAL; // 恢复到正常状态
				}
			}
			else  {
				// 检查每个按钮的悬停状态
				for (int i = 0; i < 10; i++) {
					if (isMouseOverButton(&button[i], mouseX, mouseY)) {
						button[i].state = BUTTON_HOVERED;
					}
					else {
						button[i].state = BUTTON_NORMAL;
					}
				}
			}
		}
		//SDL_RenderCopy(Renderer, textrue_background, NULL, NULL);
	
		SDL_SetRenderDrawColor(Renderer, 220, 233, 248,0xff);//设置绘制颜色
		SDL_RenderClear(Renderer);//填充颜色到渲染器
		for (int i = 0; i < 10; i++) {
			renderButton(Renderer, &button[i]);//渲染图标
		}
		SDL_RenderPresent(Renderer);
		
	}
	

	Quit();
	return 0;
}
Button createButton(ButtonState BUTTON_NORMAL, SDL_Renderer* renderer, const char* texturePath, const char* hoverTexturePath, const char* holdTexturePath, int x, int y,int w,int h, ButtonCallback callback)
{
	
	Button button;
	button.state = BUTTON_NORMAL;
	button.rect.x = x;
	button.rect.y = y;
	button.rect.w = w;  // 设置按钮宽度
	button.rect.h = h;   // 设置按钮高度
	button.texture_button = IMG_LoadTexture(renderer, texturePath);
	if (!button.texture_button) {
		printf("Failed to load texture_button: %s\n", IMG_GetError());//三种状态的纹理
	}
	button.hoverTexture = IMG_LoadTexture(renderer, hoverTexturePath);
	if (!button.hoverTexture) {
		printf("Failed to load hoverTexture : %s\n", IMG_GetError());
	}
	button.holdTexture = IMG_LoadTexture(renderer,holdTexturePath);
	if (!button.holdTexture) {
		printf("Failed to load holdTexture: %s\n", IMG_GetError());
	}
	button.callback = callback;//回调函数
	return button;
}


void Load_Surface()
{
	

}

void PreparaeAll() {
	SDL_Init(SDL_INIT_EVERYTHING);//初始化视频和事件 
	IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG);
	Window = SDL_CreateWindow(" ENCRYPTION MASTER", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width_Window, Height_Window, SDL_WINDOW_SHOWN);
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);//开
	//surface_background = IMG_Load("images/background.jpg");
	//textrue_background = SDL_CreateTextureFromSurface(Renderer, surface_background);
	for (int i = 0; i < 4; i++) {
		char buttonTexturePath[50],hoverTexturePath[50],holdTexturePath[50];  // 用于存储生成的文件路径
		snprintf(buttonTexturePath,sizeof(buttonTexturePath), "images/buttontexture%d.png", i+1);  // 使用 sprintf 拼接字符串
		snprintf(hoverTexturePath, sizeof(hoverTexturePath), "images/hovertexture%d.png", i + 1);
		snprintf(holdTexturePath, sizeof(holdTexturePath), "images/holdtexture%d.png", i + 1);
		ButtonCallback callback = NULL;
		switch (i) {
		case 0:
			callback = button1Clicked;
			break;
		case 1:
			callback = button2Clicked;
			break;
		case 2:
			callback = button3Clicked;
			break;
		case 3:
			callback = button4Clicked;
			break;
		}
		button[i] = createButton(BUTTON_NORMAL,Renderer,buttonTexturePath,hoverTexturePath,holdTexturePath , 180 + 20, i * 80 + 5+5, 160, 70,callback);
	
	}
	for (int i = 4; i < 8; i++) {
		char buttonTexturePath[50], hoverTexturePath[50], holdTexturePath[50];  // 用于存储生成的文件路径
		snprintf(buttonTexturePath, sizeof(buttonTexturePath), "images/buttontexture%d.png", i + 1);  // 使用 sprintf 拼接字符串
		snprintf(hoverTexturePath, sizeof(hoverTexturePath), "images/hovertexture%d.png", i + 1);
		snprintf(holdTexturePath, sizeof(holdTexturePath), "images/holdtexture%d.png", i + 1);
		ButtonCallback callback = NULL;
		switch (i) {
		case 4:
			callback = button5Clicked;
			break;
		case 5:
			callback = button6Clicked;
			break;
		case 6:
			callback = button7Clicked;
			break;
		case 7:
			callback = button8Clicked;
			break;
		}
		button[i] = createButton(BUTTON_NORMAL, Renderer,buttonTexturePath, hoverTexturePath, holdTexturePath, 360+20, (i-4) * 80+5+5,160,70,callback);
	
	}
	button[8]= createButton(BUTTON_NORMAL, Renderer, "images/buttontexture9.png", "images/hovertexture9.png", "images/holdtexture9.png", 20, 5+160+40,160,115, button9Clicked);
	button[9] = createButton(BUTTON_NORMAL, Renderer, "images/buttontexture11.png", "images/buttontexture11.png", "images/buttontexture11.png", 20, 10, 160, 150, button10Clicked);

}

bool isMouseOverButton(Button* button, int mouseX, int mouseY) {//判断鼠标是否在按钮上方
	return mouseX > button->rect.x && mouseX < button->rect.x + button->rect.w &&
		mouseY > button->rect.y && mouseY < button->rect.y + button->rect.h;
}
void renderButton(SDL_Renderer* renderer, Button* button) {//绘制按钮
	switch (button->state) {
	case BUTTON_HOVERED:
		SDL_RenderCopy(renderer,button->hoverTexture , NULL, &button->rect);
		break;
	case BUTTON_PRESSED:
		SDL_RenderCopy(renderer, button->holdTexture, NULL, &button->rect);
		break;
	default:
		SDL_RenderCopy(renderer, button->texture_button, NULL, &button->rect);
		break;
	}
	//SDL_RenderFillRect(renderer, &button->rect); // 填充矩形
}
void Quit() {

	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer); //关
	SDL_DestroyTexture(textrue_background);
	SDL_FreeSurface(surface_background);

	for (int i = 0; i<10; i++) {
		SDL_DestroyTexture(button[i].texture_button);
		SDL_DestroyTexture(button[i].hoverTexture);
	}
	
	IMG_Quit();
	SDL_Quit();

}

void button1Clicked() {
	printf("Button 1 clicked!\n");
    lock3(selectedFilePath, "ABC");
}

void button2Clicked() {
	printf("Button 2 clicked!\n");
    lock1(selectedFilePath, 23);
}

void button3Clicked() {
	printf("Button 3 clicked!\n");
    lock2(selectedFilePath, 13);
}

void button4Clicked() {
	printf("Button 4 clicked!\n");
    lock4(selectedFilePath, "DF");
}

void button5Clicked() {
	printf("Button 5 clicked!\n");
    ulock3(selectedFilePath, "ABC");
}

void button6Clicked() {
	printf("Button 6 clicked!\n");
    ulock1(selectedFilePath, 23);
}

void button7Clicked() {
	printf("Button 7 clicked!\n");
    ulock2(selectedFilePath, 13);
}

void button8Clicked() {
	printf("Button 8 clicked!\n");
    ulock4(selectedFilePath, "DF");
}

void button9Clicked() {
	printf("Button 9 clicked!\n");

    char group[256];
    char choice;
    int nkey;
    char ckey[256];
    int method;
    operation_func func;
    char newPath[260];


    OPENFILENAME ofn;       // 声明一个OPENFILENAME结构体，用于配置打开文件对话框  
    char szFile[260];       // 声明一个字符数组，用于存储选中的文件名  
    HANDLE hf;              // 声明一个句柄，用于后续的文件操作（此处未使用句柄进行文件操作，仅作为示例保留）  

    // 初始化OPENFILENAME结构体  
    ZeroMemory(&ofn, sizeof(ofn)); // 使用ZeroMemory函数将ofn结构体的内存清零  
    ofn.lStructSize = sizeof(ofn); // 设置结构体的大小  
    ofn.hwndOwner = NULL;          // 不指定对话框的所有者窗口  
    ofn.lpstrFile = szFile;        // 指定用于存储文件名的缓冲区  
    ofn.lpstrFile[0] = '\0';       // 将文件名字符串的第一个字符设置为'\0'，表示空字符串  
    ofn.nMaxFile = sizeof(szFile); // 设置文件名字符串的最大长度  
    ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0"; // 设置文件过滤器，这里允许选择所有文件或文本文件  
    ofn.nFilterIndex = 1;          // 设置默认的文件过滤器索引（1表示文本文件）  

    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 设置对话框标志，要求路径和文件都必须存在  

    // 显示打开文件对话框  
    if (GetOpenFileName(&ofn) == TRUE)

    {


        int i, j = 0;
        for (i = 0; newPath[i] != '\0'; i++)
        {
            if (ofn.lpstrFile[i] == '\\')
            {
                // 对于每个反斜杠，添加两个反斜杠到转义路径
                newPath[j++] = '\\';
                newPath[j++] = '\\';
            }
            else
            {
                // 其他字符直接复制
                newPath[j++] = ofn.lpstrFile[i];
            }
        }
        newPath[j] = '\0'; // 确保转义路径以空字符结尾
        // 如果用户选择了文件，则打印选中的文件名  
        printf("选中的文件: %s\n", newPath);


        // 现在newFile包含了ofn.lpstrFile的副本

        // 使用CreateFile函数尝试打开用户选中的文件 ,此处不需要，因为在函数调用里面有fopen函数，若存在会重复导致出现问题
        //hf = CreateFile(ofn.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        // 将选中的文件名复制到group变量中，用于后续操作  
        //memset(group, 0, sizeof(group)); // 使用 memset 清空 group 数组



        strncpy(group, newPath, sizeof(group) - 1);
        printf("复制的文件路径: %s\n", group);
        group[sizeof(group) - 1] = '\0'; // 确保字符串以'\0'结尾  
    }

    strncpy(selectedFilePath, newPath, sizeof(selectedFilePath) - 1);



}

void button10Clicked() {
	printf("Button 10 clicked!\n");

}

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* 丢弃字符 */ }
}



// 凯撒加密  
void lock1(const char* path, const int key)
{
    char* content = NULL;//声明一个字符指针，用于存储文件内容
    long length;         //声明一个长整型变量，用于存储文件长度
    FILE* file = fopen(path, "rb");//以二进制读取模式打开文件
    if (!file) {
        perror("加密失败：无法打开文件");
        return;
    }
    fseek(file, 0, SEEK_END);   //移动文件指针到文件末尾
    length = ftell(file);                      //获取文件长度
    fseek(file, 0, SEEK_SET);    //移动文件指针回到文件开头
    content = (char*)malloc(length + 1);         //分配内存，额外的1用于存储字符串的空终止符
    if (!content) {
        perror("内存分配失败");
        fclose(file);
        return;
    }
    fread(content, 1, length, file);//读取文件内容到内存
    content[length] = '\0';                     //添加空终止符，确保content是有效的C字符串
    fclose(file);


    //对文件内容进行凯撒加密
    for (long i = 0; i < length; i++) {
        if (isalpha(content[i]))   //如果字符是字母 
        {
            char base = isupper(content[i]) ? 'A' : 'a';//确定字母的基数（大小写）
            content[i] = (content[i] - base + key) % 26 + base;   //应用凯撒加密
        }
    }

    file = fopen(path, "wb");   //以二进制写入模式打开文件
    if (!file) {
        perror("加密失败：无法写入文件");
        free(content);
        return;
    }
    fwrite(content, 1, length, file);//将加密后的内容写回文件
    fclose(file);
    free(content);            //释放内存
    printf("文件加密成功\n");
}
// 凯撒解密  
void ulock1(const char* path, const int key)
{
    char* content = NULL;
    long length;
    FILE* file = fopen(path, "rb");
    if (!file)
    {
        perror("4加密失败：无法打开文件");
        return;
    }
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    content = (char*)malloc(length + 1);
    if (!content)
    {
        perror("内存分配失败");
        fclose(file);
        return;
    }
    fread(content, 1, length, file);
    content[length] = '\0';
    fclose(file);

    for (long i = 0; i < length; i++)
    {
        if (isalpha(content[i]))
        {
            char base = isupper(content[i]) ? 'A' : 'a';
            content[i] = (content[i] - base - key + 26) % 26 + base;
        }
    }

    file = fopen(path, "wb");
    if (!file)
    {
        perror("加密失败：无法写入文件");
        free(content);
        return;
    }
    fwrite(content, 1, length, file);
    fclose(file);
    free(content);
    printf("文件解密成功\n");
}


// 异或加密  
void lock2(const char* path, const int key)
{
    char* content = NULL;
    long length;
    FILE* file = fopen(path, "rb");
    if (!file) {
        perror("5加密失败：无法打开文件");
        return;
    }
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    content = (char*)malloc(length + 1);
    if (!content) {
        perror("内存分配失败");
        fclose(file);
        return;
    }
    fread(content, 1, length, file);
    content[length] = '\0';
    fclose(file);

    for (long i = 0; i < length; i++) {
        content[i] ^= key;
    }

    file = fopen(path, "wb");
    if (!file) {
        perror("加密失败：无法写入文件");
        free(content);
        return;
    }
    fwrite(content, 1, length, file);
    fclose(file);
    free(content);
    printf("文件加密成功\n");
}
// 异或解密
void ulock2(const char* path, const int key) 
{
    lock2(path, key);
}


// 维吉尼亚加密  
void lock3(const char* path, const char* key) 
{
    char* content = NULL;
    long length;
    FILE* file = fopen(path, "rb");
    if (!file)
    {
        perror("1加密失败：无法打开文件");
        return;
    }
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    content = (char*)malloc(length + 1);
    if (!content) {
        perror("内存分配失败");
        fclose(file);
        return;
    }
    fread(content, 1, length, file);
    content[length] = '\0';
    fclose(file);

    //初始化密钥索引和密钥长度
    int j = 0;
    int m = strlen(key);
    //对文件内容进行维吉尼亚加密
    for (long i = 0; i < length; i++)
    {
        if (isalpha(content[i]))   //检查当前字符是否为字母
        {
            char base = isupper(content[i]) ? 'A' : 'a';  //确定字母基数（大小写）
            //应用维吉尼亚加密公式：（P-'A'+K-'A'）%26+'A'
            //其中P是明文中的字母，K是密钥中的字母
            //两者都转换为0-25的数值进行计算，然后对26取余，最后转换回字符
            content[i] = (content[i] - base + toupper(key[j % m]) - 'A') % 26 + base;
            j++;   //移动到密钥中的下一个字符，j%m确保密钥索引j在密钥长度m范围内循环
        }
    }

    file = fopen(path, "wb");
    if (!file) {
        perror("加密失败：无法写入文件");
        free(content);
        return;
    }
    fwrite(content, 1, length, file);
    fclose(file);
    free(content);
    printf("文件加密成功\n");
}
// 维吉尼亚解密  
void ulock3(const char* path, const char* key)
{
    char* content = NULL;
    long length;
    FILE* file = fopen(path, "rb");
    if (!file)
    {
        perror("解密失败：无法打开文件");
        return;
    }
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    content = (char*)malloc(length + 1);
    if (!content)
    {
        perror("内存分配失败");
        fclose(file);
        return;
    }
    fread(content, 1, length, file);
    content[length] = '\0';
    fclose(file);

    int j = 0;
    int m = strlen(key);
    for (long i = 0; i < length; i++)
    {
        if (isalpha(content[i]))
        {
            char base = isupper(content[i]) ? 'A' : 'a';
            content[i] = (content[i] - base - (toupper(key[j % m]) - 'A') + 26) % 26 + base;
            j++;
        }
    }

    file = fopen(path, "wb");
    if (!file)
    {
        perror("解密失败：无法写入文件");
        free(content);
        return;
    }
    fwrite(content, 1, length, file);
    fclose(file);
    free(content);
    printf("文件解密成功\n");
}


// 字符串加密  
void lock4(const char* path, const char* key)
{
    char* content = NULL;
    long length;
    FILE* file = fopen(path, "rb");
    if (!file)
    {
        perror("加密失败：无法打开文件");
        return;
    }
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    content = (char*)malloc(length + 1);
    if (!content)
    {
        perror("内存分配失败");
        fclose(file);
        return;
    }
    fread(content, 1, length, file);
    content[length] = '\0';
    fclose(file);

    int l = strlen(key);
    int i = 0;
    for (long j = 0; j < length; j++)
    {
        //如果密钥索引超出密钥长度，重置为0
        if (i >= l) i = 0;
        //应用加密公式： (C+K)%(CHAR_MAX-CHAR_MIN+1)+CHAR_MIN
        //其中C是文件内容中的字符，K是密钥中的字符
        //CHAR_MIN和CHAR_MAX分别是字符类型能表示的最大值和最小值
        content[j] = (content[j] - CHAR_MIN + (unsigned char)key[i]) % (CHAR_MAX - CHAR_MIN + 1) + CHAR_MIN;
        //移动到密钥中的下一个字符
        i++;     
    }

    file = fopen(path, "wb");
    if (!file)
    {
        perror("加密失败：无法写入文件");
        free(content);
        return;
    }
    fwrite(content, 1, length, file);
    fclose(file);
    free(content);
    printf("文件加密成功\n");
}
// 字符串解密  
void ulock4(const char* path, const char* key)
{

    char* content = NULL;
    long length;
    FILE* file = fopen(path, "rb");
    if (!file)
    {
        perror("解密失败：无法打开文件");
        return;
    }
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    content = (char*)malloc(length + 1);
    if (!content)
    {
        perror("内存分配失败");
        fclose(file);
        return;
    }
    fread(content, 1, length, file);
    content[length] = '\0';
    fclose(file);

    int l = strlen(key);
    int i = 0;
    for (long j = 0; j < length; j++)
    {
        if (i >= l) i = 0;
        // 逆转加密变换  
        content[j] = ((unsigned char)content[j] - CHAR_MIN - (unsigned char)key[i] + (CHAR_MAX - CHAR_MIN + 1)) % (CHAR_MAX - CHAR_MIN + 1) + CHAR_MIN;
        i++;
    }
    file = fopen(path, "wb");
    if (!file)
    {
        perror("解密失败：无法写入文件");
        free(content);
        return;
    }
    fwrite(content, 1, length, file);
    fclose(file);
    free(content);
    printf("文件解密成功\n");
}



//加密复杂度和强度比较
/*
凯撒加密：

复杂度：非常低。凯撒加密是一种简单的替换加密，每个字母在字母表中移动固定的位置。
强度：非常弱。由于密钥空间小（只有26个可能的密钥），凯撒加密很容易被破解，特别是通过频率分析。

异或加密：

复杂度：低。异或加密通过将每个字节与一个固定密钥进行异或操作来加密数据。
强度：相对较弱。如果密钥长度不够长或者密钥被重复使用，这种加密方法可以被破解。
维吉尼亚加密：

复杂度：中等。维吉尼亚加密使用一个密钥序列对数据进行加密，其中密钥长度与明文相同。
强度：较强。由于使用了密钥序列，这种加密方法比凯撒和异或加密更难以破解，尤其是当密钥足够长且随机时。
字符串加密：

复杂度：中等。这种加密方法通过将文件内容与一个密钥字符串进行某种数学运算来加密。
强度：取决于密钥和算法的具体实现。如果密钥足够长且随机，且算法设计得当，这种加密方法可以提供较强的安全性。
*/