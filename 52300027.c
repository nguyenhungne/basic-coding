#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int tinhKhiWind(int n, int dc, int dg, int ld);
int tinhKhiRain(int n, int dc, int dg, int ld);
int tinhKhiSun(int n, int dc, int dg, int ld);
int tinhKhiCloud(int n, int dc, int dg, int ld);
int tinhKhiFog(int n, int dc, int dg, int ld);

int main()
{
    int n, dc, dg, ld;
    char w[10];

    FILE *file = fopen("input.inp", "r");
    if (file == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    if (fscanf(file, "%d %d %d %d %s", &n, &dc, &dg, &ld, w) != 5)
    {
        printf("Failed to read from file\n");
        return 1;
    }

    fclose(file);

    // scanf("%d %d %d %d %s", &n, &dc, &dg, &ld, w);

    if (n < 0 || n > 2000)
    {
        FILE *file = fopen("output.out", "w");
        if (file == NULL)
        {
            printf("Cannot open file\n");
            return 1;
        }

        fprintf(file, "%d %d %d", -1, -1, n);

        fclose(file);
        printf("%d %d %d", -1, -1, n);
        return 1;
    }

    if (dc == 0 && dg == 0)
    {
        FILE *file = fopen("output.out", "w");
        if (file == NULL)
        {
            printf("Cannot open file\n");
            return 1;
        }

        fprintf(file, "%d %d %d", -1, -1, n);
        printf("%d %d %d", -1, -1, n);
        return 1;
    }

    if (ld < 1 || ld > 600)
    {
        FILE *file = fopen("output.out", "w");
        if (file == NULL)
        {
            printf("Cannot open file\n");
            return 1;
        }

        fprintf(file, "%d %d %d", -1, -1, n);
        printf("%d %d %d", -1, -1, n);
        return 1;
    }

    if (strlen(w) == 0)
    {
        FILE *file = fopen("output.out", "w");
        if (file == NULL)
        {
            printf("Cannot open file\n");
            return 1;
        }

        fprintf(file, "%d %d %d", -1, -1, n);
        printf("%d %d %d", -1, -1, n);
        return 1;
    }

    float PI = 3.1415926535;

    if (strcmp(w, "Wind") == 0)
    {
        tinhKhiWind(n, dc, dg, ld);
        return 0;
    }

    else if (strcmp(w, "Rain") == 0)
    {
        tinhKhiRain(n, dc, dg, ld);
    }

    else if (strcmp(w, "Sun") == 0)
    {
        tinhKhiSun(n, dc, dg, ld);
    }

    else if (strcmp(w, "Cloud") == 0)
    {
        tinhKhiCloud(n, dc, dg, ld);
    }

    else if (strcmp(w, "Fog") == 0)
    {
        tinhKhiFog(n, dc, dg, ld);
    }

    return 0;
}

int tinhKhiWind(int n, int dc, int dg, int ld)

{
    int bc = 0, bg = 0;
    float nd = 0;

    float PI = 3.1415926535;
    float soNepBanhChung = dc * dc * sqrt(dc);
    float soNepBanhGiay = (dg * dg * PI) / 3;
    bc = (soNepBanhChung == 0) ? 0 : n / soNepBanhChung;
    nd = (float)n - (bc * soNepBanhChung);
    bg = (soNepBanhGiay == 0) ? 0 : nd / soNepBanhGiay;

    nd = nd - (bg * soNepBanhGiay);

    int ldBc = (dc >= 8) ? 2 : 1;
    int ldBg = (dg >= 5) ? 2 : 1;
    int laDongCanDung = (bg * ldBg) + (bc * ldBc);

    while (laDongCanDung > ld)
    {
        bc = 0;
        bg = 0;
        while (1)
        {
            float nextBcNep = (bc + 1) * soNepBanhChung;
            float nextBgNep = (bg + 1) * soNepBanhGiay;
            int nextBcLaDong = (bc + 1) * ldBc;
            int nextBgLaDong = (bg + 1) * ldBg;

            if (nextBcNep + bg * soNepBanhGiay <= n && nextBcLaDong + bg * ldBg <= ld && nextBcNep > nextBgNep)
            {
                bc++;
            }
            else if (bc * soNepBanhChung + nextBgNep <= n && bc * ldBc + nextBgLaDong <= ld)
            {
                bg++;
            }
            else
            {
                break;
            }

            laDongCanDung = (bg * ldBg) + (bc * ldBc);
            nd = n - (bc * soNepBanhChung + bg * soNepBanhGiay);
        }
    }
    nd = floorf(nd * 1000) / 1000;
    printf("%d %d %.3f", bc, bg, nd);

    FILE *file = fopen("output.out", "w");
    if (file == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    fprintf(file, "%d %d %.3f", bc, bg, nd);

    fclose(file);
    return 0;
}

int tinhKhiRain(int n, int dc, int dg, int ld)
{
    int bc = 0, bg = 0;
    float nd = 0;

    float PI = 3.1415926535;
    float soNepBanhChung = dc * dc * sqrt(dc);
    float soNepBanhGiay = (dg * dg * PI) / 3;

    int tongNepCan = soNepBanhChung + soNepBanhGiay;
    bc = bg = n / tongNepCan;
    nd = n - (bc * soNepBanhChung) - (bg * soNepBanhGiay);

    while (nd > soNepBanhChung || nd > soNepBanhGiay)
    {
        if (soNepBanhChung > soNepBanhGiay)
        {
            if (nd > soNepBanhChung)
            {
                bc++;
                nd = nd - soNepBanhChung;
            }
            else if (nd > soNepBanhGiay)
            {
                bg++;
                nd = nd - soNepBanhGiay;
            }
        }
        else
        {
            if (nd > soNepBanhGiay)
            {
                bg++;
                nd = nd - soNepBanhGiay;
            }
            else if (nd > soNepBanhChung)
            {
                bc++;
                nd = nd - soNepBanhChung;
            }
        }
    }

    int ldBc = (dc >= 8) ? 2 : 1;
    int ldBg = (dg >= 5) ? 2 : 1;
    int laDongCanDung = (bg * ldBg) + (bc * ldBc);

    while (laDongCanDung > ld)
    {
        if (bc > bg)
        {
            bc--;
            nd = nd + soNepBanhChung;
        }
        else
        {
            bg--;
            nd = nd + soNepBanhGiay;
        }

        laDongCanDung = (bg * ldBg) + (bc * ldBc);
    }
    nd = floorf(nd * 1000) / 1000;
    printf("%d %d %.3f", bc, bg, nd);

    FILE *file = fopen("output.out", "w");
    if (file == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    fprintf(file, "%d %d %.3f", bc, bg, nd);

    fclose(file);

    
}

// friend number
int divisorsSum(int n)
{
    int sum = 0;
    for (int i = 1; i <= n / 2; i++)
    {
        if (n % i == 0)
        {
            sum += i;
        }
    }
    return sum;
}

int isFriendNumber(int a, int b)
{
    return divisorsSum(a) == b && divisorsSum(b) == a;
}

int tinhKhiCloud(int n, int dc, int dg, int ld)
{
    int bc = 0, bg = 0;
    float nd = 0;

    float PI = 3.1415926535;
    float soNepBanhChung = dc * dc * sqrt(dc);
    float soNepBanhGiay = (dg * dg * PI) / 3;

    if (isFriendNumber(n, ld))
    {
        FILE *file = fopen("output.out", "w");
        if (file == NULL)
        {
            printf("Cannot open file\n");
            return 1;
        }

        fprintf(file, "%d %d %.3f", 0, 0,(float)n);
        printf("%d %d %.3f", 0, 0, (float)n);
        return 0;
    }
    bg = n / soNepBanhGiay;
    nd = n - (bg * soNepBanhGiay);
    while (nd > soNepBanhChung)
    {
        bc++;
        nd = nd - soNepBanhChung;
    }

    int ldBc = (dc >= 8) ? 2 : 1;
    int ldBg = (dg >= 5) ? 2 : 1;
    int laDongCanDung = (bg * ldBg) + (bc * ldBc);

    while (laDongCanDung > ld)
    {
        bc = 0;
        bg = 0;
        while (1)
        {
            float nextBcNep = (bc + 1) * soNepBanhChung;
            float nextBgNep = (bg + 1) * soNepBanhGiay;
            int nextBcLaDong = (bc + 1) * ldBc;
            int nextBgLaDong = (bg + 1) * ldBg;

            if (nextBcNep + bg * soNepBanhGiay <= n && nextBcLaDong + bg * ldBg <= ld && nextBcNep > nextBgNep)
            {
                bc++;
            }
            else if (bc * soNepBanhChung + nextBgNep <= n && bc * ldBc + nextBgLaDong <= ld)
            {
                bg++;
            }
            else
            {
                if (laDongCanDung < ld && soNepBanhChung < soNepBanhGiay && nd >= soNepBanhChung )
                {
                    bc++;
                    nd = n - (bc * soNepBanhChung + bg * soNepBanhGiay);
                    break;
                }
                else if (
                    laDongCanDung < ld && soNepBanhChung > soNepBanhGiay && nd>= soNepBanhGiay)
                {
                    bg++;
                    nd = n - (bc * soNepBanhChung + bg * soNepBanhGiay);
                    break;
                }
                else {
                    nd = n - (bc * soNepBanhChung + bg * soNepBanhGiay);
                    break;
                }
            }
            laDongCanDung = (bg * ldBg) + (bc * ldBc);
        }
    }
    printf("%d %d %.3f", bc, bg, nd);

    FILE *file = fopen("output.out", "w");
    if (file == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    fprintf(file, "%d %d %.3f", bc, bg, nd);

    fclose(file);
}

int tinhKhiSun(int n, int dc, int dg, int ld)
{

    float PI = 3.1415926535;

    int G = dc % 6;
    int H = ld % 5;

    int X = 0;

    int values[6][5] = {
        {5, 20, 15, 12, 10},
        {7, 5, 20, 15, 12},
        {10, 7, 5, 20, 15},
        {12, 10, 7, 5, 20},
        {15, 12, 10, 7, 5},
        {20, 15, 12, 10, 7}};

    if (G >= 0 && G < 6 && H >= 0 && H < 5)
    {
        X = values[G][H];
    }

    n = n + n * X / 100;
    ld = ld - X;

    // rain
    if ((dc + dg) % 3 == 0)
    {
        tinhKhiRain(n, dc, dg, ld);
    }
    // Wind
    else if ((dc + dg) % 3 == 1)
    {
        tinhKhiWind(n, dc, dg, ld);
    }
    // cloud
    else if ((dc + dg) % 3 == 2)
    {
        tinhKhiCloud(n, dc, dg, ld);
    }
}

// fibonacci
int isFibonacci(int n)
{
    int a = 0, b = 1, c = a + b;
    while (c < n)
    {
        a = b;
        b = c;
        c = a + b;
    }
    return c == n;
}

int tinhKhiFog(int n, int dc, int dg, int ld)
{
    int bc = 0, bg = 0;
    float nd = 0;

    if (isFibonacci(dc) && isFibonacci(dg))
    {
        dc = dc / 2;
        dg = dg / 2;
    }
    else
    {
        dc = dc * 2;
        dg = dg * 2;
    }

    float PI = 3.1415926535;
    float soNepBanhChung = dc * dc * sqrt(dc);
    float soNepBanhGiay = (dg * dg * PI) / 3;
    bc = (soNepBanhChung == 0) ? 0 : n / soNepBanhChung;
    nd = (float)n - (bc * soNepBanhChung);
    bg = (soNepBanhGiay == 0) ? 0 : nd / soNepBanhGiay;

    int soBanhItNhat = 0;

    if (bc < bg)
    {
        soBanhItNhat = bc;
        nd = n - (bc * soNepBanhChung);
        bg = 0;
        while (nd > soNepBanhGiay)
        {
            bg++;
            nd = nd - soNepBanhGiay;
        }
    }
    else
    {
        soBanhItNhat = bg;
        nd = n - (bg * soNepBanhGiay);
        bc = 0;
        while (nd > soNepBanhChung)
        {
            bc++;
            nd = nd - soNepBanhChung;
        }
    }

    int ldBc = (dc >= 8) ? 2 : 1;
    int ldBg = (dg >= 5) ? 2 : 1;
    int laDongCanDung = (bg * ldBg) + (bc * ldBc);
    while (laDongCanDung > ld)
{
    if (soNepBanhChung < soNepBanhGiay) {
        bc--;
    }
    else {
        bg--;
    }
    laDongCanDung = (bg * ldBg) + (bc * ldBc);
}
    nd = floorf(nd * 1000) / 1000;
    printf("%d %d %.3f", bc, bg, nd);

    FILE *file = fopen("output.out", "w");
    if (file == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    fprintf(file, "%d %d %.3f", bc, bg, nd);

    fclose(file);
}