const fs = require('fs');
const randomNormal = require('random-normal');

const initializeNetwork = {
    values: [],
    getRandWeight(previousLayerLength) { //Random number with gaussian normal distribution
        let weight = randomNormal();
        weight *= Math.sqrt(1/(previousLayerLength)); //Xavier initialization
        return weight;
    },
    init(hiddenLayersLength, neuronsPerLayerLength, inputLayerLength) {
        for(let i = 0; i <= hiddenLayersLength; i++) {
            if(i == hiddenLayersLength) neuronsPerLayerLength = 36;
            let previousLayerLength = 100;
            if(i == 0) previousLayerLength = inputLayerLength;
            this.values.push([]);
            for(let j=0; j<neuronsPerLayerLength; j++) {
                this.values[i].push([0, []]); //0 is bias
                for(let k=0; k<previousLayerLength; k++) {
                    this.values[i][j][1].push(this.getRandWeight(previousLayerLength));
                }
            }
        }
        let json = JSON.stringify(this.values);
        fs.writeFile('./../neuronalNetwork/networkValues.json', json, 'utf8', ()=> {});
    }
};

initializeNetwork.init(5, 100, 784);