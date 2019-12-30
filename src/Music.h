namespace Music
{
    enum Tracks
    {
        MUSIC_NONE=0,
        MUSIC_TITLE,
    
        MUSIC_P1,
        MUSIC_P1_1 = MUSIC_P1,
        MUSIC_P1_END = MUSIC_P1_1,
    
        MUSIC_P2,
        MUSIC_P2_6 = MUSIC_P2,
        MUSIC_P2_7,
        MUSIC_P2_8,
        MUSIC_P2_9,
        MUSIC_P2_10,
        MUSIC_P2_END = MUSIC_P2_10,

        MUSIC_P3,
        MUSIC_P3_11 = MUSIC_P3,
        MUSIC_P3_12,
        MUSIC_P3_13,
        MUSIC_P3_14,
        MUSIC_P3_END = MUSIC_P3_14,

        MUSIC_P4,
        MUSIC_P4_15 = MUSIC_P4,
        MUSIC_P4_END = MUSIC_P4_15,

        MUSIC_FINAL,
        MUSIC_FINAL_1 = MUSIC_FINAL,
        MUSIC_FINAL_2,
        MUSIC_FINAL_3,
        MUSIC_FINAL_4,
        MUSIC_FINAL_5,
    
        MUSIC_WIN,
        MUSIC_WIN_1 = MUSIC_WIN,
        MUSIC_WIN_2,
        MUSIC_WIN_3,
        MUSIC_WIN_4,
        MUSIC_EPICWIN,

        MUSIC_LOSE,
        MUSIC_LOSE_1 = MUSIC_LOSE,
        MUSIC_LOSE_2,
        MUSIC_LOSE_3,
        MUSIC_LOSE_4,
        MUSIC_LOSE_5,

        MUSIC_LETSPLAY,
        MUSIC_TIMEOUT,
        MUSIC_AWAIT,
        MUSIC_AUDIENCE,

        MUSIC_LOSE_NOOB,
        MUSIC_LOSE_10,
        MUSIC_LOSE_15,
    };

    int GetGameMusic(int world, int level);
    int GetFinalMusic(int level);
    int GetLoseMusic(int world, int level);
    int GetWinMusic(int level);
};