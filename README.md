# zhang-suen

> Implementation of the Zhang-Suen thinning (or skeletonization) algorithm. A description of the algorithm can be found here: [https://rosettacode.org/wiki/Zhang-Suen_thinning_algorithm](https://rosettacode.org/wiki/Zhang-Suen_thinning_algorithm)

## Installation

```shell
npm install --save zhang-suen
```
## Usage

```js
const zhangsuen = require('zhang-suen');

const result = zhangsuen(bitsArray, width, height); // bitsArray have to be a Uint8Array containing only 0 and 1
```

## Example

We'll apply the algorithm on the following image (`origin-img.jpg`):

![](https://olivierlando.github.io/zhang-suen/origin-img.jpg)

```js
const jpeg = require('jpeg-js');
const zhangSuen = require('zhang-suen');
const fs = require('fs');

// read the jpg file of image to be transformed
const image = jpeg.decode(fs.readFileSync('origin-img.jpg'), true);

// convert rgba pixels to bits (1 bit per pixel)
const inputBitsArray = new Uint8Array(image.width * image.height);
for (let i=0 ; i<image.data.length ; i+=4) {
    inputBitsArray[i/4] = image.data[i] < 50 && image.data[i+1] < 50 && image.data[i+2] < 50 ? 1 : 0;
}

// apply Zhang-Suen algorithm on the bits array
const outputBitsArray = zhangSuen(inputBitsArray, image.width, image.height);

// convert back Zhang Suen bits to rgba pixels
const outputPixels = outputBitsArray.reduce((res, bit, i) => {
      res.set(bit === 1 ? [0, 0, 0, 255] : [255, 255, 255, 255], i * 4);
      return res;
    },
    new Uint8Array(outputBitsArray.length * 4)
);

// generate a jpg file with these pixels
fs.writeFile("transformed-img.jpg", jpeg.encode({
    data: outputPixels,
    width: image.width,
    height: image.height,
}, 100).data);
```


The generated jpg (`transformed-img.jpg`) will look like that:

![](https://olivierlando.github.io/zhang-suen/transformed-img.jpg)