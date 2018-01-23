// generated with brms 2.0.3
functions { 

  /* compute the cloglog link 
   * Args: 
   *   p: a scalar in (0, 1)
   * Returns: 
   *   a scalar in (-Inf, Inf)
   */ 
   real cloglog(real p) { 
     return log(-log(1 - p)); 
   }
  /* sratio-cloglog log-PDF for a single response 
   * Args: 
   *   y: response category 
   *   mu: linear predictor 
   *   thres: ordinal thresholds 
   *   disc: discrimination parameter 
   * Returns: 
   *   a scalar to be added to the log posterior 
   */ 
   real sratio_cloglog_lpmf(int y, real mu, vector thres, real disc) { 
     int ncat = num_elements(thres) + 1; 
     vector[ncat] p; 
     vector[ncat - 1] q; 
     for (k in 1:(ncat - 1)) { 
       q[k] = 1 - inv_cloglog(disc * (thres[k] - mu)); 
       p[k] = 1 - q[k]; 
       for (kk in 1:(k - 1)) p[k] = p[k] * q[kk]; 
     } 
     p[ncat] = prod(q); 
     return categorical_lpmf(y | p); 
   } 
  /* sratio-cloglog log-PDF for a single response 
   * including category specific effects 
   * Args: 
   *   y: response category 
   *   mu: linear predictor 
   *   mucs: predictor for category specific effects 
   *   thres: ordinal thresholds 
   *   disc: discrimination parameter 
   * Returns: 
   *   a scalar to be added to the log posterior 
   */ 
   real sratio_cloglog_cs_lpmf(int y, real mu, row_vector mucs, vector thres, real disc) { 
     int ncat = num_elements(thres) + 1; 
     vector[ncat] p; 
     vector[ncat - 1] q; 
     for (k in 1:(ncat - 1)) { 
       q[k] = 1 - inv_cloglog(disc * (thres[k] - mucs[k] - mu)); 
       p[k] = 1 - q[k]; 
       for (kk in 1:(k - 1)) p[k] = p[k] * q[kk]; 
     } 
     p[ncat] = prod(q); 
     return categorical_lpmf(y | p); 
   } 
} 
data { 
  int<lower=1> N;  // total number of observations 
  int Y[N];  // response variable 
  int<lower=2> ncat;  // number of categories 
  int<lower=1> K;  // number of population-level effects 
  matrix[N, K] X;  // population-level design matrix 
  int<lower=1> Kcs;  // number of category specific effects
  matrix[N, Kcs] Xcs;  // category specific design matrix
  real<lower=0> disc;  // discrimination parameters 
  int prior_only;  // should the likelihood be ignored? 
} 
transformed data { 
  int Kc = K - 1; 
  matrix[N, K - 1] Xc;  // centered version of X 
  vector[K - 1] means_X;  // column means of X before centering 
  for (i in 2:K) { 
    means_X[i - 1] = mean(X[, i]); 
    Xc[, i - 1] = X[, i] - means_X[i - 1]; 
  } 
} 
parameters { 
  vector[Kc] b;  // population-level effects 
  vector[ncat-1] temp_Intercept;  // temporary thresholds 
  matrix[Kcs, ncat - 1] bcs;  // category specific effects
} 
transformed parameters { 
} 
model { 
  // linear predictor for category specific effects
  matrix[N, ncat - 1] mucs = Xcs * bcs;
  vector[N] mu = Xc * b; 
  // priors including all constants 
  target += normal_lpdf(b | 0,5); 
  target += student_t_lpdf(temp_Intercept | 3, 0, 10); 
  target += normal_lpdf(to_vector(bcs) | 0,5); 
  // likelihood including all constants 
  if (!prior_only) { 
    for (n in 1:N) { 
      target += sratio_cloglog_cs_lpmf(Y[n] | mu[n], mucs[n], temp_Intercept, disc); 
    } 
  } 
} 
generated quantities { 
  // compute actual thresholds 
  vector[ncat - 1] b_Intercept = temp_Intercept + dot_product(means_X, b); 
} 
