#include <sm64.h>

// bparam1 question number
// bparam2 correct one
class MillCtl : public MObject
{
private:
    void FreezeMario();
    void MaskInputs(int inputs);
    void SetCamera();
    void SetGamingMusic();
    void FixMusic();
    void SetMusic(int music);
    void SetWinMusic();

    void PrintHint(const char* msg, int offsetY = 0);
    
    void PickedAngle(int pick);

    int GetWorld(int q);
    int GetLevel(int q);

    // Normal states
    void Prepare();
    void Unveil();
    void Picking();
    void Final();
    void Results();
    void WalkAway();


    // Lifelines
    void FiftyFifty();
    void Audience();
    void CallFriend();
    void AudiencePicking();
    void AudienceAfterPicking();
    void CallFriendCountDown();

    void Init();
    void Step();

    static void sInit() { reinterpret_cast<MillCtl*>(M64_CURR_OBJ_PTR)->Init(); }
    static void sStep() { reinterpret_cast<MillCtl*>(M64_CURR_OBJ_PTR)->Step(); }

public:
    static int Behavior[];
};