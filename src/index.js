const zhangSuen = require('../build/Release/zhang-suen')


module.exports = function(bitsArray, width, height) {
    if(bitsArray.constructor !== Uint8Array) {
        throw Error('Uint8Array expected.')
    }
    if(bitsArray.length !== width * height) {
        throw Error('bits array size != width*height');
    }
    return zhangSuen.thin(bitsArray, width, height);
};
