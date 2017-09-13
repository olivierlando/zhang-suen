# shang-suen

> Implementation of the Zhang-Suen thinning (or skeletonization) algorithm. A description of the algorithm can be found here: [https://rosettacode.org/wiki/Zhang-Suen_thinning_algorithm](https://rosettacode.org/wiki/Zhang-Suen_thinning_algorithm)

## Installation

```shell
npm install --save shang-suen
```
## Usage

```js
const shangsuen = require('shang-suen');

const result = shangsuen(bitsArray, width, height); // bitsArray have to be a Uint8Array containing only 0 and 1
```

## Example

Applying the algorithm on the following image:

![](https://olivierlando.github.io/zhang-suen/origin-img.jpg)

Will give this result:

![](https://olivierlando.github.io/zhang-suen/transformed-img.jpg)