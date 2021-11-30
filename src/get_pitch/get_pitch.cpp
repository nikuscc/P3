/// @file

#include <iostream>
#include <fstream>
#include <string.h>
#include <errno.h>

#include <cmath>
#include "ffft/FFTReal.h"

#include "wavfile_mono.h"
#include "pitch_analyzer.h"

#include "docopt.h"

#define FRAME_LEN   0.030 /* 30 ms. */
#define FRAME_SHIFT 0.015 /* 15 ms. */

using namespace std;
using namespace upc;

static const char USAGE[] = R"(
get_pitch - Pitch Detector 
Usage:
    get_pitch [options] <input-wav> <output-txt>
    get_pitch (-h | --help)
    get_pitch --version
Options:
    -p FLOAT, --potvalue=FLOAT    Power threshold value [default: -50]
    -r FLOAT, --r1norm=FLOAT      Autocorrelation in 1 normalized threshold value [default: 0.80]
    -m FLOAT, --rmaxnorm=FLOAT    Autocorrelation on lag normalized threshold value [default: 0.30]
    -h, --help  Show this screen
    --version   Show the version of the project
Arguments:
    input-wav   Wave file with the audio signal
    output-txt  Output file: ASCII file with the result of the detection:
                    - One line per frame with the estimated f0
                    - If considered unvoiced, f0 must be set to f0 = 0
)";

int main(int argc, const char *argv[]) {
	/// \TODO 
	///  Modify the program syntax and the call to **docopt()** in order to
	///  add options and arguments to the program.
  /// \DONE
    std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
        {argv + 1, argv + argc},	// array of arguments, without the program name
        true,    // show help if requested
        "2.0");  // version string

	std::string input_wav = args["<input-wav>"].asString();
	std::string output_txt = args["<output-txt>"].asString();

  float potvalue = std::stof(args["--potvalue"].asString());
  float r1norm = std::stof(args["--r1norm"].asString());
  float rmaxnorm = std::stof(args["--rmaxnorm"].asString());

  // Read input sound file
  unsigned int rate;
  vector<float> x;
  if (readwav_mono(input_wav, rate, x) != 0) {
    cerr << "Error reading input file " << input_wav << " (" << strerror(errno) << ")\n";
    return -2;
  }

  int n_len = rate * FRAME_LEN;
  int n_shift = rate * FRAME_SHIFT;
  float max_value = *max_element(x.begin(),x.end());
  // Define analyzer
  PitchAnalyzer analyzer(n_len, rate, potvalue, r1norm, rmaxnorm, PitchAnalyzer::HAMMING, 50, 500);

  /// \TODO
  /// Preprocess the input signal in order to ease pitch estimation. For instance,
  /// central-clipping or low pass filtering may be used.
  /// \DONE

// Center-Clipping
#if 0
  for (unsigned int i = 0; i < x.size(); i++){
    if(abs(x[i]) / max_value < 0.009)
      x[i] = 0.0F;
  }
#endif

// Low-Pass Filter
#if 0
// ==================================================================================================

  ffft::FFTReal <float> fft_object1 (1024);
  std::vector<float> Xlow;
  Xlow.resize(x.size());
  fft_object1.do_fft(Xlow.data(),x.data());

  std::vector<float> lpf;
  lpf.resize(x.size());
  float cutoff_fl = 2000; 
  int k = (cutoff_fl/rate)*x.size(); 

  for(int n = 0;n < k; n++){
    lpf[n] = 0;
  } 
  for(int n = k; n < x.size(); n++){
    lpf[n] = 1;
  } 
  for(int n = 0 ; n < Xlow.size(); n++){
    Xlow[n] *= lpf[n];
  }

  fft_object1.do_ifft (Xlow.data(), x.data());
  fft_object1.rescale (x.data());
 // ==================================================================================================*/
#endif

//High-Pass Filter
#if 0
// ==================================================================================================

  ffft::FFTReal <float> fft_object2 (1024);
  std::vector<float> Xhigh;
  Xhigh.resize(x.size());
  fft_object2.do_fft(Xhigh.data(),x.data());


  std::vector<float> hpf;
  hpf.resize(x.size());
  float cutoff_fh = 50;
  int kh = (cutoff_fh/rate)*x.size();

  for(int n = 0;n < kh; n++){
    hpf[n] = 0;
  } 
  for(int n = kh; n < x.size(); n++){
    hpf[n] = 1;
  } 
  for(int n = 0 ; n < Xhigh.size(); n++){
    Xhigh[n] *= hpf[n];
  }

  fft_object2.do_ifft (Xhigh.data(), x.data());
  fft_object2.rescale (x.data());
 // ==================================================================================================*/
#endif

  // Iterate for each frame and save values in f0 vector
  vector<float>::iterator iX;
  vector<float> f0;
  for (iX = x.begin(); iX + n_len < x.end(); iX = iX + n_shift) {
    float f= analyzer(iX, iX + n_len);
    f0.push_back(f);
  }

  /// \TODO
  /// Postprocess the estimation in order to supress errors. For instance, a median filter
  /// or time-warping may be used.
  /// \DONE
#if 0

  unsigned int M = 3;
  vector<float> median_window(M);

  for (unsigned int i = (M-1)/2; i < f0.size() - (M-1)/2; i++){
    for (int m = 0; m < M; m++){
      median_window[m]=f0[i+m-((M-1)/2)];
    }
    sort(median_window.begin(),median_window.end());

    f0[i]=median_window[(M-1)/2]; // Agafar l'element central
  }

#endif

  // Write f0 contour into the output file
  ofstream os(output_txt);
  if (!os.good()) {
    cerr << "Error reading output file " << output_txt << " (" << strerror(errno) << ")\n";
    return -3;
  }

  os << 0 << '\n'; //pitch at t=0
  for (iX = f0.begin(); iX != f0.end(); ++iX) 
    os << *iX << '\n';
  os << 0 << '\n';//pitch at t=Dur

  return 0;
}
