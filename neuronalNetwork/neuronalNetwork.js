const network = {
    input: [],
    values: [],
    neuronActivations: [],
    init(inputNeuronActivations, values) {
        this.input = inputNeuronActivations;
        this.values = values;
        this.mainProcess();
        let outputLayer = new Array();
        this.neuronActivations[this.neuronActivations.length - 1].forEach((el, ix, arr)=> {
            outputLayer.push(el);
        });
        let heighestValue = Math.max(...outputLayer);
        let index =  outputLayer.indexOf(heighestValue);
        if(index < 10) return index.toString();
        let letters = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"];
        return letters[index-10];
    },
    mainProcess() {
        for(i = 0; i<values.length; i++) {
            this.neuronActivations.push([]);
            let previousLayerLength = i > 0 ? values[i-1].length : 784;
            for(let j=0; j<values[i].length; j++) {
                let bias = values[i][j][0];
                let z = bias;
                for(let k=0; k<previousLayerLength; k++) {
                    let a = i > 0 ? this.neuronActivations[i-1][k] : this.input[k];
                    z += a*values[i][j][1][k];
                }
                this.neuronActivations[i][j] = this.tanh(z);
            }
        }
    },
    tanh(x) {
        return (1 - (2 / (Math.exp(2 * x) + 1))); //tanh(x) = 1 - 2/(1+ e^2x)
    }
}

const fs = require('fs');
let inputNeuronActivations = new Array(784),
    jsonFile = fs.readFileSync('networkValues.json');
let values = JSON.parse(jsonFile);
for(let i=0; i<inputNeuronActivations.length; i++) {
    inputNeuronActivations[i] = Math.random();      //random input
}
let output = network.init(inputNeuronActivations, values);
console.log(output);