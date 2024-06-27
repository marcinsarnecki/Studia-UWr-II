/**
 * 
 * @param {number} max 
 * @returns 
 */
function getRandomInt(max) {
    return Math.floor(Math.random() * max);
  }


class Item {
    /**
     * 
     * @param {string} name 
     * @param {number} amount 
     * @param {Date} date 
     * @param {number} price 
     */
    constructor(name, amount, date) {
        this.id = getRandomInt(1000000000)
        this.name = name
        this.amount = amount
        this.date = date
        this.price = -1 // -1 means it's not set 
        this.state = false
    }
}

/**
 * 
 * @param {Array} array 
 * @param {Item} item 
 * @returns {number}
 */
function addItem(array, item) {
    array.push(item)
    return array[array.length-1].id
}

/**
 * 
 * @param {Array} array 
 * @param {number} id 
 */
function eraseItem(array, id) {
    let elementPos = array.map(item => item.id).indexOf(id);
    if(elementPos != -1)
        array.splice(elementPos, 1)
}

/**
 * 
 * @param {Array} array 
 * @param {number} id 
 * @param {string} name 
 */
function editName(array, id, name) {
    let elementPos = array.map(item => item.id).indexOf(id);
    if(elementPos != -1)
        array[elementPos].name = name
}

/**
 * 
 * @param {Array} array 
 * @param {number} id 
 * @param {boolean} state 
 */
function editState(array, id, state) {
    let elementPos = array.map(item => item.id).indexOf(id);
    if(elementPos != -1)
        array[elementPos].state = state
}

/**
 * 
 * @param {Array} array 
 * @param {number} id 
 * @param {number} amount 
 */
 function editAmount(array, id, amount) {
    let elementPos = array.map(item => item.id).indexOf(id);
    if(elementPos != -1)
        array[elementPos].amount = amount
}

/**
 * 
 * @param {Array} array 
 * @param {number} id 
 * @param {Date} date
 */
 function editDate(array, id, date) {
    let elementPos = array.map(item => item.id).indexOf(id);
    if(elementPos != -1)
        array[elementPos].date = date
}


/**
 * 
 * @param {Array} array 
 * @param {number} id 
 * @param {number} price 
 */
function editPrice(array, id, price) {
    let elementPos = array.map(item => item.id).indexOf(id);
    if(elementPos != -1)
        array[elementPos].price = price
}


function changeOrder(array, idx1, idx2) {
    if(idx1 >= array.length || idx2 >= array.length)
        return null
    let tmp = array[idx1]
    array[idx1] = array[idx2]
    array[idx2] = tmp
}

/**
 * 
 * @param {Array} array 
 */
function checkToday(array) {
    const today = new Date()
    const result = array.filter(item => item.date.toDateString() === today.toDateString())
    for(let i = 0; i < result.length; i += 1)
        console.log(result[i])
}

/**
 * 
 * @param {Array} array 
 * @param {Date} date 
 * @returns {number}
 */
function sumByDay(array, date) {
    const result = array.filter(item => (item.date.toDateString() === date.toDateString() && item.state))
    return result.map(item => item.price * item.amount).reduce((partialSum, a) => partialSum + a, 0)
}

/**
 * 
 * @param {Array} array 
 * @param {Array} idList 
 * @param {callback} f
 */
function formatArray(array, idList, f) {
    array.map(item => (idList.includes(item.id) ? f(item) : item))
}



let itemArray = []

let id1 = addItem(itemArray, new Item("aaa", 3, new Date(2022, 10, 20)))
let id2 = addItem(itemArray, new Item("bbb", 4, new Date(2022, 10, 20)))
let id3 = addItem(itemArray, new Item("ccc", 5, new Date(2022, 10, 20)))
let id4 = addItem(itemArray, new Item("ddd", 5, new Date(2022, 10, 25)))
let id5 = addItem(itemArray, new Item("eee", 5, new Date(2022, 10, 24)))
let id6 = addItem(itemArray, new Item("fff", 5, new Date(2022, 10, 24)))
let id7 = addItem(itemArray, new Item("ggg", 5, new Date(2022, 10, 20)))
let id8 = addItem(itemArray, new Item("hhh", 5, new Date(2022, 10, 20)))
let id9 = addItem(itemArray, new Item("iii", 100, new Date(2022, 10, 20)))


console.log(itemArray[0].name, itemArray[1].name, itemArray[2].name, itemArray[3].name) //aaa bbb ccc ddd
eraseItem(itemArray, id2)
eraseItem(itemArray, id4)
console.log(itemArray[0].name, itemArray[1].name, itemArray[2].name, itemArray[3].name) //aaa ccc eee fff



console.log(itemArray[0].name, itemArray[1].name) // aaa ccc ...
changeOrder(itemArray, 0, 1)
console.log(itemArray[0].name, itemArray[1].name) // ccc aaa ...

checkToday(itemArray)

editState(itemArray, id1, true)
editState(itemArray, id3, true)
editState(itemArray, id7, true)
editState(itemArray, id8, true)
editPrice(itemArray, id1, 3)    // 3 * 3 = 9    //
editPrice(itemArray, id3, 2)    // 2 * 5 = 10   // sum = 84
editPrice(itemArray, id7, 3)    // 3 * 5 = 15   // 
editPrice(itemArray, id8, 10)   // 10 * 5 = 50  //
editPrice(itemArray, id9, 100)  // 100 * 100 = 10000 // state = false
console.log("bbb", itemArray);

console.log("sum = ", sumByDay(itemArray, new Date(2022, 10, 20)))





/**
 * 
 * @param {number} item 
 */
function convertToDollars(item) {
    item.price *= 4.52
}

console.log(itemArray[0])
console.log(itemArray[1])
console.log(itemArray[2])
// console.log("ccc", itemArray);
formatArray(itemArray, [id1, id3], convertToDollars)
// console.log("ddd", itemArray);
console.log(itemArray[0])
console.log(itemArray[1])
console.log(itemArray[2])












