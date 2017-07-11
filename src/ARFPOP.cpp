/* -*- compile-command: "R CMD INSTALL .." -*- */

#include <vector>
#include <stdio.h>
#include "funPieceListLog.h"
#include <math.h>

void ARFPOP
  (double *data_vec, int data_count,
   double penalty,
   // the following matrices are for output.
   // cost_mat and intervals_mat store the optimal cost and number of intervals
   // at each time point, for the up and down cost models.
   // end_vec and mean_vec store the best model up to and including the
   // last data point.
   double gam, // decay parameter
   double *cost_mat,
   int *end_vec, //data_count
   double *mean_vec,//data_count
   int *intervals_mat,//data_count
   bool *constraint){
  double min_mean=-INFINITY, max_mean=INFINITY;
  
  std::vector<PiecewiseSquareLoss> cost_model_mat(data_count);
  PiecewiseSquareLoss *cost, *cost_prev;
  PiecewiseSquareLoss min_prev_cost, scaled_prev_cost, min_prev_cost_scaled;
  int verbose=0;
  for(int data_i=0; data_i<data_count; data_i++){
    cost = &cost_model_mat[data_i];
    // Alg 3, ln 4
    if(data_i==0){
      cost->piece_list.emplace_back
      (1.0, -2 * data_vec[0], data_vec[0] * data_vec[0],
       min_mean, max_mean, -1, false);
      
    }else{ // Alg 3 ln 6 - 8
      
      
      scaled_prev_cost.set_to_scaled_of(cost_prev, gam, verbose);
      
      if (*constraint) {
        min_prev_cost.set_to_min_less_of(cost_prev, verbose);
      } else {
        min_prev_cost.set_to_unconstrained_min_of(cost_prev, verbose);
      }
      
      min_prev_cost.set_prev_seg_end(data_i-1);
      min_prev_cost.add(0.0, 0.0, penalty);
      
      min_prev_cost_scaled.set_to_scaled_of(&min_prev_cost, gam, verbose);
      
      cost->set_to_min_env_of(&min_prev_cost_scaled, &scaled_prev_cost, verbose);
      cost->add
        (1.0,
         -2 * data_vec[data_i], data_vec[data_i] * data_vec[data_i]);
    }
    
    cost_prev = cost;
    
  }
  
  // Decoding the cost_model_vec, and writing to the output matrices.
  double best_cost, best_mean, prev_mean;
  int prev_seg_end=data_count;
  
  for(int i=0; i< data_count; i++){
    cost = &cost_model_mat[i];
    intervals_mat[i] = cost->piece_list.size();
    cost->Minimize
      (cost_mat+i, &best_mean,
       &prev_seg_end, &prev_mean);
        // printf("=cost function* at data_i %d\n", i);
        // cost -> print();
  }
  
  
  // first step
  cost = &cost_model_mat[data_count - 1];
  cost->Minimize
    (&best_cost, &best_mean,
     &prev_seg_end, &prev_mean);
  
  //    mean_vec[0] = best_mean;
  //    end_vec[0] = prev_seg_end;
  
  
  int prev_seg_old = data_count - 1;
  int out_i=0;
  double mean = best_mean;
  
   // printf("last mean %f\n", mean);
   // printf("prev_seg_end %d\n", prev_seg_end);
  
  
  // loop over all prev. changepoints
  double temp_mean;
  while(prev_seg_old >= 0){
    
    if (prev_seg_old < data_count - 1) {
      cost = &cost_model_mat[prev_seg_end];
      cost -> findMean
        (mean, &prev_seg_end, &prev_mean);
      
     // temp_mean = mean;
     // 
     // cost->Minimize
     //   (&best_cost, &mean,
     //    &prev_seg_end, &prev_mean);
     // 
     // printf("Found mean %f versus %f min mean\n", temp_mean, mean);
      
    }
    
    
    for (int t = prev_seg_old; t > prev_seg_end; t--){
      mean_vec[out_i] = mean;
      end_vec[out_i] = prev_seg_end;
      mean /= gam;
      out_i++;
    }
    
    prev_seg_old = prev_seg_end;
    
    if (prev_seg_old >= 0) {
      if(prev_mean < INFINITY){
        //equality constraint inactive
        mean = prev_mean;
      }
    }
    
  }
}