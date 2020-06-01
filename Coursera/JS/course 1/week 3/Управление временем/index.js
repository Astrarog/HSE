/**
 * @param {String} date
 * @returns {Object}
 */
module.exports = function (date) {
    var dateRegexp = /(\d{4})-(\d{2})-(\d{2}) (\d{2}):(\d{2})/;

    var match = date.match(dateRegexp);
    // console.log(match);
    var d = new Date(match[1], match[2] - 1, match[3], match[4], match[5]);

    // var d = new Date(date);
    Object.defineProperty(d, 'add', {value: function (count, unit) {

        if(count<0)
        {
            throw TypeError("First argument should be >= 0");
        }
        switch (unit) {
            case "years":
                this.setUTCFullYear(this.getUTCFullYear()+count);
                break;
            case "months":
                this.setUTCMonth(this.getUTCMonth()+count);
                break;
            case "days":
                this.setUTCDate(this.getUTCDate()+count);
                break;
            case "hours":

                this.setUTCHours(this.getUTCHours()+count);
                break;
            case "minutes":
                this.setUTCMinutes(this.getUTCMinutes()+count);
                break;
            default:
                throw TypeError("Unknown unit");

        }
        // console.log(this.toString());
        return this; },
        writable: false,
        enumerable: false,
        configurable: false});
    Object.defineProperty(d, 'subtract', {value: function (count, unit) {
            if(count<0)
            {
                throw TypeError("First argument should be >= 0");
            }
            switch (unit) {
                case "years":
                    this.setUTCFullYear(this.getUTCFullYear()-count);
                    break;
                case "months":
                    this.setUTCMonth(this.getUTCMonth()-count);
                    break;
                case "days":
                    this.setUTCDate(this.getUTCDate()-count);
                    break;
                case "hours":

                    this.setUTCHours(this.getUTCHours()-count);
                    break;
                case "minutes":
                    this.setUTCMinutes(this.getUTCMinutes()-count);
                    break;
                default:
                    throw TypeError("Unknown unit");

            }
            // console.log(this.toString());
            return this; },
        writable: false,
        enumerable: false,
        configurable: false});


    Object.defineProperty(d, 'value',
{get: function () {
        // console.log(this.getFullYear()+ '-' + addZero(this.getMonth()+1)+'-' +addZero(this.getDate()) + ' '+ addZero(this.getHours()) + ':' + addZero(this.getMinutes()))
        return this.getFullYear()+ '-' + addZero(this.getMonth()+1)+'-' +addZero(this.getDate()) + ' '+ addZero(this.getHours()) + ':' + addZero(this.getMinutes());
            }
        });
    return d;
};


function addZero(num) {
    return num < 10 ? '0' + num : num;
}