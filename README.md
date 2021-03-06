# LTNC-project
Cao Tiến Thắng - 21020403 - K66CD - UET
## Giới thiệu
Môn học: Lập trình nâng cao - INT 2215_1

Bài tập lớn - Game (Sokoban)
### Table of contents:
**[Mô tả chung về trò chơi](#mô-tả-chung-về-trò-chơi)**

**[Cách cài đặt game](#cách-cài-đặt-game)**

**[Các chức năng đã cài đặt](#các-chức-năng-đã-cài-đặt)**

**[Các kỹ thuật lập trình được sử dụng](#các-kỹ-thuật-lập-trình-được-sử-dụng)**

**[Kết luận](#kết-luận)**

## Mô tả chung về trò chơi
Đây là phiên bản làm lại của game giải đố sokoban cổ điển, đồng thời thêm thắt một vài tính năng nhỏ cho gameplay thêm phong phú.
Phần game cổ điển bao gồm:
- Nhân vật chính
- Hộp
- Goal (Dấu 'X')
- Tường

Luật chơi như sau: Ta sẽ điều khiển nhân vật chính đẩy toàn bộ số hộp vào vị trí của dấu X, tuy nhiên không chỉ đơn giản như vậy.
Tường sẽ giới hạn phạm vi di chuyển của nhân vật, đồng thời nhân vật chỉ có thể đẩy chứ không thể kéo và không thể đẩy 2 hộp cùng một lúc.
## Cách cài đặt game
- Bước 1: Trên trang github này bấm vào nút Code (như hình minh họa):
![B1](https://user-images.githubusercontent.com/100329563/169662470-7099069d-df30-4302-a5a3-f79e53ee6256.png)
- Bước 2: Bấm vào Donwnload Zip để tải về:
![B2](https://user-images.githubusercontent.com/100329563/169662543-ce395ba0-8bd6-441f-8f0f-a39efab8f699.png)
- Bước 3: Giải nén, sau khi giải nén ta được 1 folder có tên là LTNC-project, mở folder lên và file chạy sokoban.exe để chơi:
![B3](https://user-images.githubusercontent.com/100329563/169662703-5ab71ced-77f9-4a88-82d5-2ae2966f3cf3.png)
## Các chức năng đã cài đặt:
- Main menu gồm có các nút:
  - ![CasualButtons_Locked_001](https://user-images.githubusercontent.com/100329563/169691374-8630b4df-7c55-43cb-839b-78c9ed734c1b.png) : Bắt đầu chơi từ level 1.
  - ![levels_mouse_out](https://user-images.githubusercontent.com/100329563/169691393-cbe4582f-58dc-4d6f-8931-2663c23a8086.png) : Chọn các level mình muốn chơi (từ 1 - 105), di chuột vào level nào sẽ được xem trước level đó, những level nào đã hoàn thành sẽ được tô màu xanh lá. Nút ![CasualIcons_Locked_035](https://user-images.githubusercontent.com/100329563/169693433-46f6c591-73e1-4027-9f4c-3ae1dfdfcef1.png) sẽ xóa hết các điểm số trước đó.
  - ![CasualButtons_Locked_008](https://user-images.githubusercontent.com/100329563/169691437-f5265e10-8329-4b3f-bb56-a16389cc70ea.png) : Hướng dẫn chơi game.
  - ![credits_mouse_out](https://user-images.githubusercontent.com/100329563/169691475-da4229a0-bfdf-4db0-80fa-8c1f1ab87119.png) : Tác giả của game.
  - ![CasualButtons_Locked_009](https://user-images.githubusercontent.com/100329563/169691496-df729442-9d96-4533-89ec-129bd8a8af22.png) : Thoát game.
- In Game:
  - Bấm phím mũi tên để di chuyển, mỗi lần bấm sẽ di chuyển được 1 ô, không được đi qua tường, khi đi qua hộp sẽ đẩy hộp theo, được đi vào goal.
  - Nút ![CasualIcons_Locked_020](https://user-images.githubusercontent.com/100329563/169683765-b80d916d-f004-49c3-ac8e-b7dfa9a0258d.png) dùng để bật/tắt âm thanh.
  - Nút ![CasualIcons_Locked_006](https://user-images.githubusercontent.com/100329563/169683710-09b7c065-d0f6-4f0c-ae0a-d5e303a3fb7a.png) dùng để trở về main menu.
  - Nút ![CasualIcons_Locked_004](https://user-images.githubusercontent.com/100329563/169683783-9c03b08d-3df7-4938-b22b-bbfc44074b2d.png) dùng để replay lại level đang chơi.
  - Nút ![CasualIcons_Locked_023](https://user-images.githubusercontent.com/100329563/169683801-1e491ab2-d491-4b3e-b832-af7510546d30.png) dùng để hoàn tác lại các bước đi trước đó.
  - Nút ![CasualIcons_Locked_025](https://user-images.githubusercontent.com/100329563/169683853-fd221379-eed2-460e-b37e-cdac32a8a528.png)![CasualIcons_Locked_026](https://user-images.githubusercontent.com/100329563/169683858-f76a4093-2496-4d4f-826b-9b5706216eae.png) tương ứng để tăng giảm level.
- Điểm số: 
  - Mỗi level sẽ được ghi lại điểm số, đó là số bước di chuyển và thời gian, số bước ít nhất và thời gian ngắn nhất để hoàn thành level sẽ được ghi vào kỷ lục.
- Nhạc:
  - Nhạc nền sẽ chạy trong suốt game, có thể bật/tắt tùy ý.
  - Khi hoàn thành 1 level sẽ có màn hình thông báo sẽ có 1 tiếng ting được phát lên.
  ![win_image](https://user-images.githubusercontent.com/100329563/170060219-8b78abe8-30a8-4acd-b097-45973752ffd4.png)
- [video demo](https://www.youtube.com/watch?v=p_IewL05KVQ)
## Các kỹ thuật lập trình được sử dụng:
- Thư viện đồ họa SDL2.
- Kiến thức về lập trình hướng đối tượng (OOP).
- Thư viện mixer để xử lí âm thanh.
- Thư viện fstream để đọc, ghi lại điểm ra file txt.
- Mảng, vector để lưu trữ lại vị trí của nhân vật, hộp. Mảng 2 chiều để lưu trữ map ...
- Lớp LTexture để định nghĩa các vật thể trong game (nhân vật, hộp, tường, sàn, ...):
```C++
class LTexture
{
public:
    LTexture ();
    ~LTexture ();
    bool loadFromFile (SDL_Renderer* renderer, string path);
    bool loadFromRenderedText (SDL_Renderer* renderer, TTF_Font* font, string textureText, SDL_Color textColor);
    void free();
    void setColor (Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode (SDL_BlendMode blending);
    void setAlpha (Uint8 alpha);
    void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0,
                SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    bool checkCollision(SDL_Rect a, SDL_Rect b);
    void setPosX (int x);
    void setPosY (int y);
    int getWidth();
    int getHeight ();
    int getPosX ();
    int getPosY ();
    SDL_Rect getRect();
private:
    SDL_Texture* texture;
    int mWidth;
    int mHeight;
protected:
    int posX,posY;
};  
```
- Kỹ thuật tách file, module hóa chương trình.
- Xử lí va chạm.
```C++
bool LTexture::checkCollision(SDL_Rect a, SDL_Rect b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }
    //If none of the sides from A are outside B
    return true;
}
```
- Xử lí các sự kiện từ bàn phím và chuột.
- Một số kỹ năng tính toán toán học để xác định vị trí đặt nút bấm.
## Kết luận:
- Sau bài tập lớn này em cảm thấy kiến thức và kỹ năng lập trình của em được mở rộng, nâng cao đáng kể, em đã:
   - Học được cách sử dụng thuần thục thư viện đồ họa SDL2.
   - Nâng cao kỹ năng tách file, module hóa, clean code để quản lí code lớn, dễ dàng refactor, hướng tới làm lập trình viên chuyên nghiệp.
   - Nâng cao khả năng tự học, tự tìm tòi kiến thức, tự tìm cách fix bug.
- Hướng phát triển thêm cho dự án:
  - Phát triển thêm tính năng gợi ý cách giải.
  - Thêm tính năng tự động thay đổi kích cỡ map (khi map qua lớn và window không thể chứa hết thì lúc đó sẽ tự động giảm kích cỡ map cho vừa với window).
  - Cải thiện về chất lượng đồ họa.
  - Tiếp tục thiết kế thêm nhiều map hơn.
  - Thêm tính năng như: thay đổi nhân vật, chọn bài hát, thêm nhiều sound efect.
- Điều tâm đắc rút ra được sau khi hoàn thiện chương trình: 
  - Nhiều khi, sau khi lên ý tưởng, ta thấy quá khó để thực hiện. Tuy nhiên, chỉ cần chia nhỏ vấn đề ra và giải quyết từng cái một, ta sẽ thấy nó không khó như vậy.
  - 99% project của em là tự code, nên em hiểu được sự ý nghĩa của chương trình mà mình tự code ra. Cho nên, mặc dù có thể tham khảo nhưng tự code vẫn là tốt nhất.
