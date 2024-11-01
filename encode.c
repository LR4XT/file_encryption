 //�п����й�
#define _CRT_SECURE_NO_WARNINGS
#include "common.h"

//����������Ҫһ��window һ������

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
char selectedFilePath[260];//ȫ�ֱ�����ź����ڵ��ļ�·��
int main(int argc, char* argv[]) {//main���ڴ��������
	bool buttonHovered = false;
    char* path;
	
	PreparaeAll();
	int mouseX, mouseY;

	//SDL_RenderPresent(Renderer);

	//SDL_Delay(2000);
	while (1) {
		
		SDL_GetMouseState(&mouseX, &mouseY);//��ȡ���״̬
		while (SDL_PollEvent(&event))//sdl_event�ȴ��¼�
		{
			if (event.type == SDL_QUIT) {
				Quit();
				return 0;
			}

			else if (event.type == SDL_MOUSEBUTTONDOWN) {
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);

				// �����갴��״̬
				for (int i = 0; i < 10; i++) {
					if (isMouseOverButton(&button[i], mouseX, mouseY)) {
						button[i].state = BUTTON_PRESSED;
					}
				}
			}
			else if (event.type == SDL_MOUSEBUTTONUP) {
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);

				// �������ͷ�״̬
				for (int i = 0; i < 10; i++) {
					if (isMouseOverButton(&button[i], mouseX, mouseY)) {
						if (button[i].callback) {
							button[i].callback();
						}
						//������Ӧ��ִ�к���
					
						//printf("Button %d clicked!\n", i + 1);
					}
					button[i].state = BUTTON_NORMAL; // �ָ�������״̬
				}
			}
			else  {
				// ���ÿ����ť����ͣ״̬
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
	
		SDL_SetRenderDrawColor(Renderer, 220, 233, 248,0xff);//���û�����ɫ
		SDL_RenderClear(Renderer);//�����ɫ����Ⱦ��
		for (int i = 0; i < 10; i++) {
			renderButton(Renderer, &button[i]);//��Ⱦͼ��
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
	button.rect.w = w;  // ���ð�ť���
	button.rect.h = h;   // ���ð�ť�߶�
	button.texture_button = IMG_LoadTexture(renderer, texturePath);
	if (!button.texture_button) {
		printf("Failed to load texture_button: %s\n", IMG_GetError());//����״̬������
	}
	button.hoverTexture = IMG_LoadTexture(renderer, hoverTexturePath);
	if (!button.hoverTexture) {
		printf("Failed to load hoverTexture : %s\n", IMG_GetError());
	}
	button.holdTexture = IMG_LoadTexture(renderer,holdTexturePath);
	if (!button.holdTexture) {
		printf("Failed to load holdTexture: %s\n", IMG_GetError());
	}
	button.callback = callback;//�ص�����
	return button;
}


void Load_Surface()
{
	

}

void PreparaeAll() {
	SDL_Init(SDL_INIT_EVERYTHING);//��ʼ����Ƶ���¼� 
	IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG);
	Window = SDL_CreateWindow(" ENCRYPTION MASTER", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width_Window, Height_Window, SDL_WINDOW_SHOWN);
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);//��
	//surface_background = IMG_Load("images/background.jpg");
	//textrue_background = SDL_CreateTextureFromSurface(Renderer, surface_background);
	for (int i = 0; i < 4; i++) {
		char buttonTexturePath[50],hoverTexturePath[50],holdTexturePath[50];  // ���ڴ洢���ɵ��ļ�·��
		snprintf(buttonTexturePath,sizeof(buttonTexturePath), "images/buttontexture%d.png", i+1);  // ʹ�� sprintf ƴ���ַ���
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
		char buttonTexturePath[50], hoverTexturePath[50], holdTexturePath[50];  // ���ڴ洢���ɵ��ļ�·��
		snprintf(buttonTexturePath, sizeof(buttonTexturePath), "images/buttontexture%d.png", i + 1);  // ʹ�� sprintf ƴ���ַ���
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

bool isMouseOverButton(Button* button, int mouseX, int mouseY) {//�ж�����Ƿ��ڰ�ť�Ϸ�
	return mouseX > button->rect.x && mouseX < button->rect.x + button->rect.w &&
		mouseY > button->rect.y && mouseY < button->rect.y + button->rect.h;
}
void renderButton(SDL_Renderer* renderer, Button* button) {//���ư�ť
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
	//SDL_RenderFillRect(renderer, &button->rect); // ������
}
void Quit() {

	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer); //��
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


    OPENFILENAME ofn;       // ����һ��OPENFILENAME�ṹ�壬�������ô��ļ��Ի���  
    char szFile[260];       // ����һ���ַ����飬���ڴ洢ѡ�е��ļ���  
    HANDLE hf;              // ����һ����������ں������ļ��������˴�δʹ�þ�������ļ�����������Ϊʾ��������  

    // ��ʼ��OPENFILENAME�ṹ��  
    ZeroMemory(&ofn, sizeof(ofn)); // ʹ��ZeroMemory������ofn�ṹ����ڴ�����  
    ofn.lStructSize = sizeof(ofn); // ���ýṹ��Ĵ�С  
    ofn.hwndOwner = NULL;          // ��ָ���Ի���������ߴ���  
    ofn.lpstrFile = szFile;        // ָ�����ڴ洢�ļ����Ļ�����  
    ofn.lpstrFile[0] = '\0';       // ���ļ����ַ����ĵ�һ���ַ�����Ϊ'\0'����ʾ���ַ���  
    ofn.nMaxFile = sizeof(szFile); // �����ļ����ַ�������󳤶�  
    ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0"; // �����ļ�����������������ѡ�������ļ����ı��ļ�  
    ofn.nFilterIndex = 1;          // ����Ĭ�ϵ��ļ�������������1��ʾ�ı��ļ���  

    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // ���öԻ����־��Ҫ��·�����ļ����������  

    // ��ʾ���ļ��Ի���  
    if (GetOpenFileName(&ofn) == TRUE)

    {


        int i, j = 0;
        for (i = 0; newPath[i] != '\0'; i++)
        {
            if (ofn.lpstrFile[i] == '\\')
            {
                // ����ÿ����б�ܣ����������б�ܵ�ת��·��
                newPath[j++] = '\\';
                newPath[j++] = '\\';
            }
            else
            {
                // �����ַ�ֱ�Ӹ���
                newPath[j++] = ofn.lpstrFile[i];
            }
        }
        newPath[j] = '\0'; // ȷ��ת��·���Կ��ַ���β
        // ����û�ѡ�����ļ������ӡѡ�е��ļ���  
        printf("ѡ�е��ļ�: %s\n", newPath);


        // ����newFile������ofn.lpstrFile�ĸ���

        // ʹ��CreateFile�������Դ��û�ѡ�е��ļ� ,�˴�����Ҫ����Ϊ�ں�������������fopen�����������ڻ��ظ����³�������
        //hf = CreateFile(ofn.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        // ��ѡ�е��ļ������Ƶ�group�����У����ں�������  
        //memset(group, 0, sizeof(group)); // ʹ�� memset ��� group ����



        strncpy(group, newPath, sizeof(group) - 1);
        printf("���Ƶ��ļ�·��: %s\n", group);
        group[sizeof(group) - 1] = '\0'; // ȷ���ַ�����'\0'��β  
    }

    strncpy(selectedFilePath, newPath, sizeof(selectedFilePath) - 1);



}

void button10Clicked() {
	printf("Button 10 clicked!\n");

}

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* �����ַ� */ }
}



// ��������  
void lock1(const char* path, const int key)
{
    char* content = NULL;//����һ���ַ�ָ�룬���ڴ洢�ļ�����
    long length;         //����һ�������ͱ��������ڴ洢�ļ�����
    FILE* file = fopen(path, "rb");//�Զ����ƶ�ȡģʽ���ļ�
    if (!file) {
        perror("����ʧ�ܣ��޷����ļ�");
        return;
    }
    fseek(file, 0, SEEK_END);   //�ƶ��ļ�ָ�뵽�ļ�ĩβ
    length = ftell(file);                      //��ȡ�ļ�����
    fseek(file, 0, SEEK_SET);    //�ƶ��ļ�ָ��ص��ļ���ͷ
    content = (char*)malloc(length + 1);         //�����ڴ棬�����1���ڴ洢�ַ����Ŀ���ֹ��
    if (!content) {
        perror("�ڴ����ʧ��");
        fclose(file);
        return;
    }
    fread(content, 1, length, file);//��ȡ�ļ����ݵ��ڴ�
    content[length] = '\0';                     //��ӿ���ֹ����ȷ��content����Ч��C�ַ���
    fclose(file);


    //���ļ����ݽ��п�������
    for (long i = 0; i < length; i++) {
        if (isalpha(content[i]))   //����ַ�����ĸ 
        {
            char base = isupper(content[i]) ? 'A' : 'a';//ȷ����ĸ�Ļ�������Сд��
            content[i] = (content[i] - base + key) % 26 + base;   //Ӧ�ÿ�������
        }
    }

    file = fopen(path, "wb");   //�Զ�����д��ģʽ���ļ�
    if (!file) {
        perror("����ʧ�ܣ��޷�д���ļ�");
        free(content);
        return;
    }
    fwrite(content, 1, length, file);//�����ܺ������д���ļ�
    fclose(file);
    free(content);            //�ͷ��ڴ�
    printf("�ļ����ܳɹ�\n");
}
// ��������  
void ulock1(const char* path, const int key)
{
    char* content = NULL;
    long length;
    FILE* file = fopen(path, "rb");
    if (!file)
    {
        perror("4����ʧ�ܣ��޷����ļ�");
        return;
    }
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    content = (char*)malloc(length + 1);
    if (!content)
    {
        perror("�ڴ����ʧ��");
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
        perror("����ʧ�ܣ��޷�д���ļ�");
        free(content);
        return;
    }
    fwrite(content, 1, length, file);
    fclose(file);
    free(content);
    printf("�ļ����ܳɹ�\n");
}


// ������  
void lock2(const char* path, const int key)
{
    char* content = NULL;
    long length;
    FILE* file = fopen(path, "rb");
    if (!file) {
        perror("5����ʧ�ܣ��޷����ļ�");
        return;
    }
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    content = (char*)malloc(length + 1);
    if (!content) {
        perror("�ڴ����ʧ��");
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
        perror("����ʧ�ܣ��޷�д���ļ�");
        free(content);
        return;
    }
    fwrite(content, 1, length, file);
    fclose(file);
    free(content);
    printf("�ļ����ܳɹ�\n");
}
// ������
void ulock2(const char* path, const int key) 
{
    lock2(path, key);
}


// ά�����Ǽ���  
void lock3(const char* path, const char* key) 
{
    char* content = NULL;
    long length;
    FILE* file = fopen(path, "rb");
    if (!file)
    {
        perror("1����ʧ�ܣ��޷����ļ�");
        return;
    }
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    content = (char*)malloc(length + 1);
    if (!content) {
        perror("�ڴ����ʧ��");
        fclose(file);
        return;
    }
    fread(content, 1, length, file);
    content[length] = '\0';
    fclose(file);

    //��ʼ����Կ��������Կ����
    int j = 0;
    int m = strlen(key);
    //���ļ����ݽ���ά�����Ǽ���
    for (long i = 0; i < length; i++)
    {
        if (isalpha(content[i]))   //��鵱ǰ�ַ��Ƿ�Ϊ��ĸ
        {
            char base = isupper(content[i]) ? 'A' : 'a';  //ȷ����ĸ��������Сд��
            //Ӧ��ά�����Ǽ��ܹ�ʽ����P-'A'+K-'A'��%26+'A'
            //����P�������е���ĸ��K����Կ�е���ĸ
            //���߶�ת��Ϊ0-25����ֵ���м��㣬Ȼ���26ȡ�࣬���ת�����ַ�
            content[i] = (content[i] - base + toupper(key[j % m]) - 'A') % 26 + base;
            j++;   //�ƶ�����Կ�е���һ���ַ���j%mȷ����Կ����j����Կ����m��Χ��ѭ��
        }
    }

    file = fopen(path, "wb");
    if (!file) {
        perror("����ʧ�ܣ��޷�д���ļ�");
        free(content);
        return;
    }
    fwrite(content, 1, length, file);
    fclose(file);
    free(content);
    printf("�ļ����ܳɹ�\n");
}
// ά�����ǽ���  
void ulock3(const char* path, const char* key)
{
    char* content = NULL;
    long length;
    FILE* file = fopen(path, "rb");
    if (!file)
    {
        perror("����ʧ�ܣ��޷����ļ�");
        return;
    }
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    content = (char*)malloc(length + 1);
    if (!content)
    {
        perror("�ڴ����ʧ��");
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
        perror("����ʧ�ܣ��޷�д���ļ�");
        free(content);
        return;
    }
    fwrite(content, 1, length, file);
    fclose(file);
    free(content);
    printf("�ļ����ܳɹ�\n");
}


// �ַ�������  
void lock4(const char* path, const char* key)
{
    char* content = NULL;
    long length;
    FILE* file = fopen(path, "rb");
    if (!file)
    {
        perror("����ʧ�ܣ��޷����ļ�");
        return;
    }
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    content = (char*)malloc(length + 1);
    if (!content)
    {
        perror("�ڴ����ʧ��");
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
        //�����Կ����������Կ���ȣ�����Ϊ0
        if (i >= l) i = 0;
        //Ӧ�ü��ܹ�ʽ�� (C+K)%(CHAR_MAX-CHAR_MIN+1)+CHAR_MIN
        //����C���ļ������е��ַ���K����Կ�е��ַ�
        //CHAR_MIN��CHAR_MAX�ֱ����ַ������ܱ�ʾ�����ֵ����Сֵ
        content[j] = (content[j] - CHAR_MIN + (unsigned char)key[i]) % (CHAR_MAX - CHAR_MIN + 1) + CHAR_MIN;
        //�ƶ�����Կ�е���һ���ַ�
        i++;     
    }

    file = fopen(path, "wb");
    if (!file)
    {
        perror("����ʧ�ܣ��޷�д���ļ�");
        free(content);
        return;
    }
    fwrite(content, 1, length, file);
    fclose(file);
    free(content);
    printf("�ļ����ܳɹ�\n");
}
// �ַ�������  
void ulock4(const char* path, const char* key)
{

    char* content = NULL;
    long length;
    FILE* file = fopen(path, "rb");
    if (!file)
    {
        perror("����ʧ�ܣ��޷����ļ�");
        return;
    }
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    content = (char*)malloc(length + 1);
    if (!content)
    {
        perror("�ڴ����ʧ��");
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
        // ��ת���ܱ任  
        content[j] = ((unsigned char)content[j] - CHAR_MIN - (unsigned char)key[i] + (CHAR_MAX - CHAR_MIN + 1)) % (CHAR_MAX - CHAR_MIN + 1) + CHAR_MIN;
        i++;
    }
    file = fopen(path, "wb");
    if (!file)
    {
        perror("����ʧ�ܣ��޷�д���ļ�");
        free(content);
        return;
    }
    fwrite(content, 1, length, file);
    fclose(file);
    free(content);
    printf("�ļ����ܳɹ�\n");
}



//���ܸ��ӶȺ�ǿ�ȱȽ�
/*
�������ܣ�

���Ӷȣ��ǳ��͡�����������һ�ּ򵥵��滻���ܣ�ÿ����ĸ����ĸ�����ƶ��̶���λ�á�
ǿ�ȣ��ǳ�����������Կ�ռ�С��ֻ��26�����ܵ���Կ�����������ܺ����ױ��ƽ⣬�ر���ͨ��Ƶ�ʷ�����

�����ܣ�

���Ӷȣ��͡�������ͨ����ÿ���ֽ���һ���̶���Կ�������������������ݡ�
ǿ�ȣ���Խ����������Կ���Ȳ�����������Կ���ظ�ʹ�ã����ּ��ܷ������Ա��ƽ⡣
ά�����Ǽ��ܣ�

���Ӷȣ��еȡ�ά�����Ǽ���ʹ��һ����Կ���ж����ݽ��м��ܣ�������Կ������������ͬ��
ǿ�ȣ���ǿ������ʹ������Կ���У����ּ��ܷ����ȿ����������ܸ������ƽ⣬�����ǵ���Կ�㹻�������ʱ��
�ַ������ܣ�

���Ӷȣ��еȡ����ּ��ܷ���ͨ�����ļ�������һ����Կ�ַ�������ĳ����ѧ���������ܡ�
ǿ�ȣ�ȡ������Կ���㷨�ľ���ʵ�֡������Կ�㹻������������㷨��Ƶõ������ּ��ܷ��������ṩ��ǿ�İ�ȫ�ԡ�
*/