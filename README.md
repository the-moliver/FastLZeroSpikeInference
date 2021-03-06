# FastLZeroSpikeInference: A package for estimating spike times from calcium imaging data using an L0 penalty 

This package implements an algorithm for deconvolving calcium imaging data for a single neuron in order to estimate the times at which the neuron spikes. This algorithim is a modification of the constrained functional pruning algorithm of Hocking et al. (2017). 

This algorithm solves the optimization problems
### AR(1) model
minimize_{c1,...,cT} 0.5 sum_{t=1}^T ( y_t - c_t )^2 + lambda sum_{t=2}^T 1_{c_t neq gamma c_{t-1} }
subject to c_t >= 0, t = 1, ..., T

for the global optimum, where y_t is the observed fluorescence at the tth timepoint.

### Constrained AR(1) model 
minimize_{c1,...,cT} 0.5 sum_{t=1}^T ( y_t - c_t )^2 + lambda sum_{t=2}^T 1_{c_t neq gamma c_{t-1} }
subject to c_t >= 0, t = 1, ..., T
           c_{t} >= gamma c_{t-1}, t = 2, ..., T

Install 
-----

If ``devtools`` is installed type 

```r
devtools::install_github("jewellsean/FastLZeroSpikeInference")
```

Usage
----

Once installed type 
```{r}
library(FastLZeroSpikeInference)
```


Alpha Python Instructions
---

Below are instructions for an alpha-release of a simple c-types python wrapper for this C++ code. Only Unix type systems are currently supported. 

NB: ubuntu requires `sudo apt install clang g++` 

Within terminal, clone this repo and run the make script: 

```
git clone "https://github.com/jewellsean/FastLZeroSpikeInference.git"
cd FastLZeroSpikeInference/python
./make.sh
```

An example using this code can be viewed [here](https://github.com/jewellsean/FastLZeroSpikeInference/blob/master/examples/python/simple_example.py).

More complete installation and usage details are forthcoming! 

References
-----

Jewell and Witten (2017). [Exact Spike Train Inference Via L0 Optimization](https://arxiv.org/abs/1703.08644)

Hocking, T. D., Rigaill, G., Fearnhead, P., & Bourque, G. (2017). [A log-linear time algorithm for constrained changepoint detection](https://arxiv.org/abs/1703.03352)
