/*#include <iostream>
#include <string>
#include <random>
#include <iterator>
#include <map>
#include <set>
#include <cstdlib>
#include<time.h>
#include <ctime>

using namespace std;
typedef map<int, int>MAP;
*/

/*
One Input(nth-Prime-Number), one Output (Prime-Number)
Hidden Layers: 14
Neurons per (Hidden)Layer npl: 40
Activation-Function: ELU = max(a(e^x -1), x)
eta = 0.01
*/

/*static const int LAYERS = 15;
static const int NPL = 40;

class DataStorage {
    public:
        double default_weights[LAYERS-2][NPL][NPL];
        double in_out_layer_weights[2][NPL];

        double default_biases[LAYERS-2][NPL];
        double last_layer_bias;

        void initialiseValues() {
            //bias initialisation
            last_layer_bias = 0;
            int default_bias_length = *(&default_biases + 1) - default_biases;
            for (int i = 0; i < default_bias_length; i++) {
                int tmp = *(&default_biases[i] + 1) - default_biases[i];
                int nd_default_bias_length = tmp;
                for (int j = 0; j < nd_default_bias_length; j++) {
                    default_biases[i][j] = 0.;
                }
            }

            //weight initialisation
            default_random_engine generator;
            double standard_deviation1 = sqrt(4. / (2. * NPL)); //He Initialization
            normal_distribution<double> distribution1(0., standard_deviation1);
            for (int i = 0; i < LAYERS - 2; i++) {
                for (int j = 0; j < NPL; j++) {
                    for (int k = 0; k < NPL; k++) {
                        default_weights[i][j][k] = distribution1(generator);
                    }
                }
            }
            double standard_deviation2 = sqrt(4. / (1. + NPL)); //He Initialization
            normal_distribution<double> distribution2(0., standard_deviation2);
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < NPL; j++) {
                    in_out_layer_weights[i][j] = distribution2(generator);
                }
            }
        }

        void setDefaultWeights(double value, int layer, int neuron, int nth) {

            default_weights[layer][neuron][nth] = value;
        }
        void setFirstLayerWeights(double value, int nth) {
            in_out_layer_weights[0][nth] = value;
        }
        void setLastLayerWeights(double value, int nth) {
            in_out_layer_weights[1][nth] = value;
        }

        void setDefaultBias(double value, int layer, int nth) {
            default_biases[layer][nth] = value;
        }
        void setLastLayerBias(double value) {
            last_layer_bias = value;
        }
};

class PrimeNumbers {
    private:
        map<int, int> primeNumbers;
        bool mapContainsKey(int key) {
            map<int, int>::iterator itr;
            for (itr = primeNumbers.begin(); itr != primeNumbers.end(); itr++) {
                if (key == itr->first) return true;
            }
            return false;
        }
        bool mapContainsVal(int val) {
            map<int, int>::iterator itr;
            for (itr = primeNumbers.begin(); itr != primeNumbers.end(); itr++) {
                if (val == itr->second) return true;
            }
            return false;
        }

    public:
        bool isPrime(int n) {
            int lastGaplessPrimeNumber = 2;
            bool gaplessIteration = true;
            int keyComparison = 0;
            for (map<int, int>::iterator itr = primeNumbers.begin(); itr != primeNumbers.end(); itr++) {
                int val = itr->second;
                if (val >= n) break;
                int key = itr->first;
                if (n % val == 0) return false;
                if (key - 1 != keyComparison) {
                    gaplessIteration = false;
                    break;
                }
                keyComparison = key;
                lastGaplessPrimeNumber = val;
            }
            if (gaplessIteration && !primeNumbers.empty()) return true;
            for (int i = lastGaplessPrimeNumber; i < n; i++) {
                if (n % i == 0) return false;
            }
            return true;
        }
        int nthPrime(int n) {
            //int bn
            //return (pow(n, 3)/pow(2, (n/(bn+1)));

            if (mapContainsKey(n)) {
                return primeNumbers.find(n)->second;
            }
            int i = 2;
            int pNumbers = 0;
            do {
                if (mapContainsVal(i)) {
                    i++;
                    pNumbers++;
                    continue;
                }
                if (isPrime(i)) {
                    pNumbers++;
                    primeNumbers.insert(pair<int, int>(pNumbers, i));
                }
                cout << "\r";
                cout << pNumbers << "th primeNumber of " << n << "th primenumber";
                i++;
            } while (pNumbers < n);
            cout << endl;
            return i-1;
        }
        void printMap() {
            map<int, int>::iterator itr;
            for (itr = primeNumbers.begin(); itr != primeNumbers.end(); itr++) {
                cout << itr->first << "   " << itr->second << endl;
            }
        }
};

class Network {
    private:
        double relu(double x) {
            if (x > 0) return x;
            return 0;
        }

    public:
        double activationValues[LAYERS-1][NPL];
        double outputActivation;
        double zValues[LAYERS-1][NPL];
        double outputZ;
        int nth;

        int run(int n, DataStorage values) {
            nth = n;
            for (int i = 0; i < LAYERS; i++) {
                int previousLayerLength = (i > 0) ? NPL : 1;
                int layerLength = (i != (LAYERS - 1)) ? NPL : 1;
                cout << "";
                for (int j = 0; j < layerLength; j++) {
                    double bias = (i != (LAYERS - 1)) ? values.default_biases[i][j] : values.last_layer_bias;
                    double z = bias;
                    if (z > 1000000) {
                        cout << "";
                    }
                    for (int k = 0; k < previousLayerLength; k++) {
                        double prevA = (i > 0) ? activationValues[i - 1][k] : nth;
                        double weight;
                        switch (i) {
                            case 0:
                                weight = values.in_out_layer_weights[0][j];
                                break;
                            case (LAYERS-1):
                                weight = values.in_out_layer_weights[1][k];
                                break;
                            default:
                                weight = values.default_weights[i - 1][j][k];
                                break;
                        }
                        if (prevA > 10000000 || weight > 10000000) {
                            cout << "";
                        }
                        z += prevA * weight;
                        cout << "";
                    }
                    if (z > 10000000) {
                        cout << "";
                    }
                    cout << "";
                    if (layerLength == 1) {
                        outputActivation = relu(z);
                        outputZ = z;
                    }
                    else {
                        activationValues[i][j] = relu(z);
                        zValues[i][j] = z;
                    }
                    cout << "";
                }
            }
            return round(outputActivation);
        }

};

class NetworkTrainier {
    private:
        double eta = 0.05;
        int learningIterations = 3000;
        int testingIterations = 500;
        int primeDomain = 500000;
        Network network;
        PrimeNumbers pn;
        DataStorage values;
        map<int, int> trainingMap;
        map<int, int> testingMap;
        set<int> costAverages;

        void log(string output) {
            cout << output << endl;
        }

        double relu_(double x) {
            if (x > 0) return 1.;
            return 0.;
        }

        void prepareInputs() {
            set<int> trainingIndexes;
            set<int> testingIndexes;
            int largestVal = 1;
            log("creating Indexes...");
            do {
                int val = round(((double)rand() / RAND_MAX) * primeDomain) + 1; //(rand() % primeDomain) + 1;
                trainingIndexes.insert(val);
                if (val > largestVal) largestVal = val;
            } while (trainingIndexes.size() < learningIterations);
            do {
                int val = round(((double)rand() / RAND_MAX) * primeDomain) + 1;
                if (setContains(val, trainingIndexes)) continue;
                testingIndexes.insert(val);
                if (val > largestVal) largestVal = val;
            } while (testingIndexes.size() < testingIterations);
            log("calculating primenumbers...");
            pn.nthPrime(largestVal);
            log("saving training and testing data...");
            for (set<int>::iterator it = trainingIndexes.begin(); it != trainingIndexes.end(); it++) {
                trainingMap.insert(pair<int, int>(*it, pn.nthPrime(*it)));
            }
            for (set<int>::iterator it = testingIndexes.begin(); it != testingIndexes.end(); it++) {
                testingMap.insert(pair<int, int>(*it, pn.nthPrime(*it)));
            }
        }

        bool setContains(int val, set<int> st) {
            set<int>::iterator itr;
            for (itr = st.begin(); itr != st.end(); itr++) {
                if (val == *itr) return true;
            }
            return false;
        }

        void saveCostFctAverage() {
            double cost = 0.;
            map<int, int>::iterator itr;
            int i = 1;
            for (itr = testingMap.begin(); itr != testingMap.end(); itr++) {
                network.run(itr->first, values);
                cost += 0.5 * pow((network.outputActivation - (itr->second)), 2);
                if (i == 9) {
                    cout << "";
                }
                i++;
            }
            cost /= i;
            cout << endl;
            cout << "average cost: " << cost << endl;
            costAverages.insert(cost);
        }

        void learningIteration(int input, int output) { //using Backpropagation
            cout << "";
            int temp = network.run(input, values);

            log("calculating errors...");
            //output Layer Errors
            double lastLayerError = (network.outputActivation - output) * relu_(network.outputZ);

            //hidden Layer Errors
            double defaultErrors[LAYERS-2][NPL];
            int l = 0;
            for (int i = LAYERS - 3; i >= 0; i--) {
                int nextLayerLength = (i != (LAYERS - 3)) ? NPL : 1;
                l++;
                for (int j = 0; j < NPL; j++) {
                    double wd = 0;
                    for (int k = 0; k < nextLayerLength; k++) {
                        cout << "\r";
                        cout << "layer " << l << " of " << LAYERS - 2 << "; Neuron " << j + 1 << " of " << NPL << "; weight " << k + 1 << " of " << nextLayerLength;
                        double weight = (nextLayerLength == NPL) ? values.default_weights[i + 1][j][k] : values.in_out_layer_weights[1][j];
                        double nextLayerError = (nextLayerLength == NPL) ? defaultErrors[i + 1][k] : lastLayerError;
                        wd += weight * nextLayerError;
                        cout << "";
                    }
                    defaultErrors[i][j] = wd * relu_(network.zValues[i][j]);
                    cout << "";
                }
            }
            cout << endl;
            log("gradient descent...");
            //gradient descent
            for (int i = 0; i < LAYERS - 1; i++) {
                bool lastLayer = false;
                if (i == (LAYERS - 2)) lastLayer = true;
                int layerLength = !lastLayer ? NPL : 1;
                int previousLayerLength = (i > 0) ? NPL : 1;
                for (int j = 0; j < layerLength; j++) {
                    cout << "\r";
                    cout << "layer " << i+1 << " of " << LAYERS - 1 << "; Neuron " << j + 1 << " of " << layerLength;
                    //change bias:
                    double neuronError = !lastLayer ? defaultErrors[i][j] : lastLayerError;
                    double oldBias = !lastLayer ? values.default_biases[i][j] : values.last_layer_bias;
                    double deltaBias = (-1) * eta * neuronError;
                    double newBias = oldBias + deltaBias;
                    if (lastLayer) {
                        values.setLastLayerBias(newBias);
                    } else {
                        values.setDefaultBias(newBias, i, j);
                    }
                    if (neuronError > 500) {
                        cout << "";
                    }
                    //change weights
                    for (int k = 0; k < previousLayerLength; k++) {
                        double oldWeight;
                        double deltaWeight;
                        double newWeight;
                        switch (i) {
                            case 0:
                                oldWeight = values.in_out_layer_weights[0][j];
                                deltaWeight = (-1) * eta * neuronError * input;
                                newWeight = oldWeight + deltaWeight;
                                values.setFirstLayerWeights(newWeight, j);
                                break;
                            case (LAYERS - 1):
                                oldWeight = values.in_out_layer_weights[1][k];
                                deltaWeight = (-1) * eta * neuronError * network.activationValues[i - 1][k];
                                newWeight = oldWeight + deltaWeight;
                                values.setLastLayerWeights(newWeight, k);
                                break;
                            default:
                                oldWeight = values.default_weights[i - 1][j][k];
                                deltaWeight = (-1) * eta * neuronError * network.activationValues[i - 1][k];
                                newWeight = oldWeight + deltaWeight;
                                values.setDefaultWeights(newWeight, (i-1), j, k);
                                cout << "";
                                break;
                        }
                        cout << "";
                    }
                }
            }
            saveCostFctAverage();
        }

    public:
        DataStorage train() {
            log("preparing Inputs...");
            prepareInputs();            
            printHyperParameters();
            log("initializing values...");
            values.initialiseValues();
            log("start learning...");
            map<int, int>::iterator itr;
            int i = 1;
            for (itr = trainingMap.begin(); itr != trainingMap.end(); itr++) {
                cout << "iteration: " << i << endl;
                learningIteration(itr->first, itr->second);
                i++;
            }
            return values;
        }

        void printHyperParameters() {
            cout << "eta: " << eta << endl;
            cout << "learningIterations: " << learningIterations << endl;
            cout << "testingIterations: " << testingIterations << endl;
            cout << "primeDomain: " << primeDomain << endl;

            return;

            log("printing Training Data:");
            map<int, int>::iterator itr;
            for (itr = trainingMap.begin(); itr != trainingMap.end(); itr++) {
                cout << itr->first << "   " << itr->second << endl;
            }
            log("printing Testing Data:");
            map<int, int>::iterator itr2;
            for (itr2 = testingMap.begin(); itr2 != testingMap.end(); itr2++) {
                cout << itr2->first << "   " << itr2->second << endl;
            }
        }

        void setLearningRate(double x) {
            eta = x;
        }
        
        void setLearningIterations(int itrs) {
            if ((itrs + testingIterations) > primeDomain) return;
            learningIterations = itrs;
        }

        void setTestingIterations(int itrs) {
            if ((itrs + learningIterations) > primeDomain) return;
            testingIterations = itrs;
        }

        void setPrimeDomain(int x) {
            if (x < (learningIterations + testingIterations)) return;
            primeDomain = x;
        }
};

void endProgram() {
    std::cout << "Zum beenden beliebiges Zeichen eingeben und Enter druecken\n";
    bool x;
    cin >> x;
}

int main() {
    NetworkTrainier trainer;
    trainer.setLearningRate(0.1);
    trainer.setLearningIterations(10);
    trainer.setTestingIterations(10);
    trainer.setPrimeDomain(100);
    trainer.train();

    endProgram();
    return 0;
}*/







#include <iostream>
#include <string>
#include <random>
#include <iterator>
#include <map>
#include <set>
#include <cstdlib>
#include<time.h>
#include <ctime>

using namespace std;
typedef map<int, int>MAP;

/*
One Input(nth-Prime-Number), one Output (Prime-Number)
Hidden Layers: 14
Neurons per (Hidden)Layer npl: 40
Activation-Function: ELU = max(a(e^x -1), x)
eta = 0.01
*/

static const int LAYERS = 15;
static const int NPL = 40;

class DataStorage {
public:
    double default_weights[LAYERS - 2][NPL][NPL];
    double in_out_layer_weights[2][NPL];

    double default_biases[LAYERS - 2][NPL];
    double last_layer_bias;

    void initialiseValues() {
        //bias initialisation
        last_layer_bias = 0;
        int default_bias_length = *(&default_biases + 1) - default_biases;
        for (int i = 0; i < default_bias_length; i++) {
            int tmp = *(&default_biases[i] + 1) - default_biases[i];
            int nd_default_bias_length = tmp;
            for (int j = 0; j < nd_default_bias_length; j++) {
                default_biases[i][j] = 0.;
            }
        }

        //weight initialisation
        default_random_engine generator;
        double standard_deviation1 = sqrt(4. / (2. * NPL)); //Xavier Initialization
        normal_distribution<double> distribution1(0., standard_deviation1);
        for (int i = 0; i < LAYERS - 2; i++) {
            for (int j = 0; j < NPL; j++) {
                for (int k = 0; k < NPL; k++) {
                    default_weights[i][j][k] = distribution1(generator);
                }
            }
        }
        double standard_deviation2 = sqrt(4. / (1. + NPL)); //Xavier Initialization
        normal_distribution<double> distribution2(0., standard_deviation2);
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < NPL; j++) {
                in_out_layer_weights[i][j] = distribution2(generator);
            }
        }
    }

    void setDefaultWeights(double value, int layer, int neuron, int nth) {

        default_weights[layer][neuron][nth] = value;
    }
    void setFirstLayerWeights(double value, int nth) {
        in_out_layer_weights[0][nth] = value;
    }
    void setLastLayerWeights(double value, int nth) {
        in_out_layer_weights[1][nth] = value;
    }

    void setDefaultBias(double value, int layer, int nth) {
        default_biases[layer][nth] = value;
    }
    void setLastLayerBias(double value) {
        last_layer_bias = value;
    }
};

class PrimeNumbers {
private:
    map<int, int> primeNumbers;
    bool mapContainsKey(int key) {
        map<int, int>::iterator itr;
        for (itr = primeNumbers.begin(); itr != primeNumbers.end(); itr++) {
            if (key == itr->first) return true;
        }
        return false;
    }
    bool mapContainsVal(int val) {
        map<int, int>::iterator itr;
        for (itr = primeNumbers.begin(); itr != primeNumbers.end(); itr++) {
            if (val == itr->second) return true;
        }
        return false;
    }

public:
    bool isPrime(int n) {
        int lastGaplessPrimeNumber = 2;
        bool gaplessIteration = true;
        int keyComparison = 0;
        for (map<int, int>::iterator itr = primeNumbers.begin(); itr != primeNumbers.end(); itr++) {
            int val = itr->second;
            if (val >= n) break;
            int key = itr->first;
            if (n % val == 0) return false;
            if (key - 1 != keyComparison) {
                gaplessIteration = false;
                break;
            }
            keyComparison = key;
            lastGaplessPrimeNumber = val;
        }
        if (gaplessIteration && !primeNumbers.empty()) return true;
        for (int i = lastGaplessPrimeNumber; i < n; i++) {
            if (n % i == 0) return false;
        }
        return true;
    }
    double nthPrime(double n) {
        double bn = n;
        if (n < 0) bn *= -1;
        return (pow(n, 3) / pow(2, (n / (bn + 1))));

        /*if (mapContainsKey(n)) {
            return primeNumbers.find(n)->second;
        }
        int i = 2;
        int pNumbers = 0;
        do {
            if (mapContainsVal(i)) {
                i++;
                pNumbers++;
                continue;
            }
            if (isPrime(i)) {
                pNumbers++;
                primeNumbers.insert(pair<int, int>(pNumbers, i));
            }
            cout << "\r";
            cout << pNumbers << "th primeNumber of " << n << "th primenumber";
            i++;
        } while (pNumbers < n);
        cout << endl;
        return (i - 1);*/
    }
    void printMap() {
        map<int, int>::iterator itr;
        for (itr = primeNumbers.begin(); itr != primeNumbers.end(); itr++) {
            cout << itr->first << "   " << itr->second << endl;
        }
    }
};

class Network {
private:
    double relu(double x) {
        //return (1 - (2 / (exp(2 * x) + 1))); //tanh(x) = 1 - 2/(1+ e^2x)
        return (1 / (1 + (exp((-1) * x))));
        if (x > 0) return x;
        return 0;
    }

public:
    double activationValues[LAYERS - 1][NPL];
    double outputActivation;
    double zValues[LAYERS - 1][NPL];
    double outputZ;
    double nth;

    int run(double n, DataStorage values) {
        nth = n;
        for (int i = 0; i < LAYERS; i++) {
            int previousLayerLength = (i > 0) ? NPL : 1;
            int layerLength = (i != (LAYERS - 1)) ? NPL : 1;
            cout << "";
            for (int j = 0; j < layerLength; j++) {
                double bias = (i != (LAYERS - 1)) ? values.default_biases[i][j] : values.last_layer_bias;
                double z = bias;
                if (z > 1000000) {
                    cout << "";
                }
                for (int k = 0; k < previousLayerLength; k++) {
                    double prevA = (i > 0) ? activationValues[i - 1][k] : nth;
                    double weight;
                    switch (i) {
                    case 0:
                        weight = values.in_out_layer_weights[0][j];
                        break;
                    case (LAYERS - 1):
                        weight = values.in_out_layer_weights[1][k];
                        break;
                    default:
                        weight = values.default_weights[i - 1][j][k];
                        break;
                    }
                    if (prevA > 10000000 || weight > 10000000) {
                        cout << "";
                    }
                    z += prevA * weight;
                    if (i == 3) {
                        cout << "";
                    }
                    //cout << "prevA: " << prevA <<  "; i: " << i << "; j: " << j << "; k: " << k << endl;
                }
                if (z > 10000000) {
                    cout << "";
                }
                cout << "";
                if (layerLength == 1) {
                    outputActivation = relu(z);
                    outputZ = z;
                }
                else {
                    activationValues[i][j] = relu(z);
                    zValues[i][j] = z;
                }
                cout << "";
            }
        }
        return (int)round(outputActivation);
    }

};

class NetworkTrainier {
private:
    double eta = 0.05;
    unsigned int learningIterations = 3000;
    unsigned int testingIterations = 500;
    unsigned int primeDomain = 500000;
    Network network;
    PrimeNumbers pn;
    DataStorage values;
    map<double, double> trainingMap;
    map<double, double> testingMap;
    set<double> costAverages;

    void log(string output) {
        cout << output << endl;
    }

    double relu_(double x) {
        //return pow((1 / (exp(x) + exp((-1) * x))), 2);
        return (1 / (1 + (exp((-1) * x)))) * (1 - (1 / (1 + (exp((-1) * x)))));
        if (x > 0) return 1.;
        return 0.;
    }

    void prepareInputs() {
        set<double> trainingIndexes;
        set<double> testingIndexes;
        log("creating Indexes...");
        do {
            double val = (((double)rand() / RAND_MAX) * 2) - 1; //(rand() % primeDomain) + 1;
            trainingIndexes.insert(val);
        } while (trainingIndexes.size() < learningIterations);
        do {
            double val = (((double)rand() / RAND_MAX) * 2) - 1;
            //if (setContains(val, trainingIndexes)) continue;
            testingIndexes.insert(val);
        } while (testingIndexes.size() < testingIterations);
        log("calculating primenumbers...");
        log("saving training and testing data...");
        for (set<double>::iterator it = trainingIndexes.begin(); it != trainingIndexes.end(); it++) {
            trainingMap.insert(pair<double, double>(*it, pn.nthPrime(*it)));
        }
        for (set<double>::iterator it = testingIndexes.begin(); it != testingIndexes.end(); it++) {
            testingMap.insert(pair<double, double>(*it, pn.nthPrime(*it)));
        }
    }

    bool setContains(double val, set<double> st) {
        set<double>::iterator itr;
        for (itr = st.begin(); itr != st.end(); itr++) {
            if (val == *itr) return true;
        }
        return false;
    }

    void saveCostFctAverage() {
        double cost = 0.;
        double deviation = 0.;
        map<double, double>::iterator itr;
        double i = 1;
        for (itr = testingMap.begin(); itr != testingMap.end(); itr++) {
            network.run(itr->first, values);
            cost += 0.5 * pow((network.outputActivation - (itr->second)), 2);
            double difference = network.outputActivation - (itr->second);
            if (difference < 0) difference *= (-1);
            deviation += difference;
            i++;
        }
        cost /= i;
        deviation /= i;
        cout << endl;
        cout << "average cost: " << cost << "; average deviation: " << deviation << endl;
        costAverages.insert(cost);
    }

    void learningIteration(double input, double output) { //using Backpropagation
        network.run(input, values);

        //output Layer Errors
        double lastLayerError = (network.outputActivation - output) * relu_(network.outputZ);

        //hidden Layer Errors
        double defaultErrors[LAYERS - 2][NPL];
        int l = 0;
        for (int i = LAYERS - 3; i >= 0; i--) {
            int nextLayerLength = (i != (LAYERS - 3)) ? NPL : 1;
            l++;
            for (int j = 0; j < NPL; j++) {
                double wd = 0;
                for (int k = 0; k < nextLayerLength; k++) {
                    cout << "\r";
                    //cout << "layer " << l << " of " << LAYERS - 2 << "; Neuron " << j + 1 << " of " << NPL << "; weight " << k + 1 << " of " << nextLayerLength;
                    double weight = (nextLayerLength == NPL) ? values.default_weights[i + 1][j][k] : values.in_out_layer_weights[1][j];
                    double nextLayerError = (nextLayerLength == NPL) ? defaultErrors[i + 1][k] : lastLayerError;
                    wd += weight * nextLayerError;
                }
                defaultErrors[i][j] = wd * relu_(network.zValues[i][j]);
            }
        }
        cout << endl;
        //gradient descent
        for (int i = 0; i < LAYERS - 1; i++) {
            bool lastLayer = false;
            if (i == (LAYERS - 2)) lastLayer = true;
            int layerLength = !lastLayer ? NPL : 1;
            int previousLayerLength = (i > 0) ? NPL : 1;
            for (int j = 0; j < layerLength; j++) {
                cout << "\r";
                //cout << "layer " << i+1 << " of " << LAYERS - 1 << "; Neuron " << j + 1 << " of " << layerLength;
                //change bias:
                double neuronError = !lastLayer ? defaultErrors[i][j] : lastLayerError;
                double oldBias = !lastLayer ? values.default_biases[i][j] : values.last_layer_bias;
                double deltaBias = (-1) * eta * neuronError;
                double newBias = oldBias + deltaBias;
                if (lastLayer) {
                    values.setLastLayerBias(newBias);
                }
                else {
                    values.setDefaultBias(newBias, i, j);
                }
                if (neuronError > 500) {
                    cout << "";
                }
                //change weights
                for (int k = 0; k < previousLayerLength; k++) {
                    double oldWeight;
                    double deltaWeight;
                    double newWeight;
                    switch (i) {
                    case 0:
                        oldWeight = values.in_out_layer_weights[0][j];
                        deltaWeight = (-1) * eta * neuronError * input;
                        newWeight = oldWeight + deltaWeight;
                        values.setFirstLayerWeights(newWeight, j);
                        break;
                    case (LAYERS - 1):
                        oldWeight = values.in_out_layer_weights[1][k];
                        deltaWeight = (-1) * eta * neuronError * network.activationValues[i - 1][k];
                        newWeight = oldWeight + deltaWeight;
                        values.setLastLayerWeights(newWeight, k);
                        break;
                    default:
                        oldWeight = values.default_weights[i - 1][j][k];
                        deltaWeight = (-1) * eta * neuronError * network.activationValues[i - 1][k];
                        newWeight = oldWeight + deltaWeight;
                        values.setDefaultWeights(newWeight, (i - 1), j, k);
                        break;
                    }
                }
            }
        }
        //eta += .009;
        saveCostFctAverage();
    }

public:
    DataStorage train() {
        log("preparing Inputs...");
        prepareInputs();
        printHyperParameters();
        log("initializing values...");
        values.initialiseValues();
        log("start learning...");
        map<double, double>::iterator itr;
        int i = 1;
        for (itr = trainingMap.begin(); itr != trainingMap.end(); itr++) {
            cout << "iteration: " << i << endl;
            learningIteration(itr->first, itr->second);
            i++;
        }
        return values;
    }

    void printHyperParameters() {
        cout << "eta: " << eta << endl;
        cout << "learningIterations: " << learningIterations << endl;
        cout << "testingIterations: " << testingIterations << endl;
        cout << "primeDomain: " << primeDomain << endl;

        return;

        log("printing Training Data:");
        map<double, double>::iterator itr;
        for (itr = trainingMap.begin(); itr != trainingMap.end(); itr++) {
            cout << itr->first << "   " << itr->second << endl;
        }
        log("printing Testing Data:");
        map<double, double>::iterator itr2;
        for (itr2 = testingMap.begin(); itr2 != testingMap.end(); itr2++) {
            cout << itr2->first << "   " << itr2->second << endl;
        }
    }

    void setLearningRate(double x) {
        eta = x;
    }

    void setLearningIterations(int itrs) {
        if ((itrs + testingIterations) > primeDomain) return;
        learningIterations = itrs;
    }

    void setTestingIterations(int itrs) {
        if ((itrs + learningIterations) > primeDomain) return;
        testingIterations = itrs;
    }

    void setPrimeDomain(unsigned int x) {
        if (x < (learningIterations + testingIterations)) return;
        primeDomain = x;
    }
};

void endProgram() {
    std::cout << "Zum beenden beliebiges Zeichen eingeben und Enter druecken\n";
    bool x;
    cin >> x;
}

int main() {
    NetworkTrainier trainer;
    trainer.setLearningRate(0.8);
    trainer.setLearningIterations(5000);
    trainer.setTestingIterations(500);
    trainer.setPrimeDomain(100);
    trainer.train();



    endProgram();
    return 0;
}