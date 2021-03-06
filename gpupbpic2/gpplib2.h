/* header file for gpplib2.c */

void cgppcacguard2l(float complex g_cu[], float g_cue[], float g_scs[],
                    float scs[], float scr[], int nx, int nyp,
                    int kstrt, int nvp, int ndim, int nxe, int nypmx,
                    int nxvh, int kypd);

void cgppcaguard2l(float complex g_q[], float g_qe[], float g_scs[],
                   float scs[], float scr[], int nx, int nyp, int kstrt,
                   int nvp, int nxe, int nypmx, int nxvh, int kypd);

void cgppcbguard2l(float complex g_fxyz[], float g_fxyze[],
                   float g_scs[], float scs[], float scr[], int nx,
                   int nyp, int kstrt, int nvp, int ndim, int nxe,
                   int nypmx, int nxvh, int kypd);

void cwappfft2rcs(float complex g_f[], float complex g_g[],
                  float complex g_bsm[], float complex g_brm[],
                  float complex bsm[], float complex brm[], int isign,
                  int g_mixup[], float complex g_sct[], float ttp[],
                  int indx, int indy, int kstrt, int nvp, int kxpd,
                  int kyp, int nxhd, int nyd, int kypd, int nxhyd,
                  int nxyhd);

void cwappfft2rcsn(float complex g_fn[], float complex g_gn[],
                   float complex g_bsm[], float complex g_brm[],
                   float complex bsm[], float complex brm[], int isign,
                   int g_mixup[], float complex g_sct[], float ttp[],
                   int indx, int indy, int kstrt, int nvp, int ndim,
                   int kxpd, int kyp, int nxhd, int nyd, int kypd,
                   int nxhyd, int nxyhd);

void gpuppfft2rrcu(float complex g_f[], float complex g_g[],
                   float complex g_bsm[], float complex g_brm[],
                   float complex bsm[], float complex brm[], int isign,
                   float ttp[], int indx, int indy, int kstrt, int nvp,
                   int kxpd, int kyp, int nxhd, int nyd, int kypd);

void gpuppfft2rrcun(float complex g_fn[], float complex g_gn[],
                    float complex g_bsm[], float complex g_brm[],
                    float complex bsm[], float complex brm[], int isign,
                    float ttp[], int indx, int indy, int kstrt, int nvp,
                    int ndim, int kxpd, int kyp, int nxhd, int nyd,
                    int kypd);

void cgpporder2l(float g_ppart[], float g_ppbuff[], float g_sbufl[],
                 float g_sbufr[], int g_kpic[], int g_ncl[],
                 int g_ihole[], int g_ncll[], int g_nclr[], 
                 float sbufl[], float sbufr[], float rbufl[], 
                 float rbufr[], int ncll[], int nclr[], int mcll[],
                 int mclr[], float ttp[], int noff, int nyp, int kstrt,
                 int nvp, int idimp, int nppmx, int nx, int ny, int mx,
                 int my, int mx1, int myp1, int npbmx, int ntmax,
                 int nbmax, int *g_irc);

void cgpptpose(float complex g_bsm[], float complex g_btm[], 
               float complex sm[], float complex tm[], int nx, int ny,
               int kxp, int kyp, int kstrt, int nvp);

void cgpptposen(float complex g_bsm[], float complex g_btm[],
                float complex sm[], float complex tm[], int nx, int ny,
                int kxp, int kyp, int kstrt, int nvp, int ndim);
