const libraryStore = [];

String.prototype.capitalize = function() { 
  return this.length === 0 ? '' : this[0].toUpperCase() + this.slice(1)
}

console.log('alice'.capitalize())

function capitalize(s) {
  return s.length === 0 ? '' : s[0].toUpperCase() + s.slice(1);
}

function capitalizeSentence(s) {
  return s.split(' ').map(capitalize).join(' ');
}

console.log(capitalize('alice')) // 'Alice'
console.log(capitalize('')) // ''

console.log(capitalizeSentence('alice in Wonderland'))

console.log("------------------");

class Media {
  _title; // dla pól prywatnych zastosowałem podejście _nazwa
  _ratings;
  _available;
  constructor(props) {
    if(!props.hasOwnProperty('title'))
      throw 'title not passed!';
    if(typeof props.title !== 'string') {
      throw 'title passed is not string!'
    }
    this._title = capitalizeSentence(props.title);
    this._ratings = [];
    this._available = true;
  }
  getTitle() {
    return this._title;
  }
  getRatings() {
    return this._ratings;
  }
  getAvailable() {
    return this._available;
  }
  addRating(x) {
    this._ratings.push(x);
  }

  orderMedia() {
    return new Promise((resolve, reject) => {
      if (this._available) {
        setTimeout(() => { //potrzeba dwóch arrow functions ze względu na this
          this._available = false;
          resolve();
        }, 1000)
        return;
      }

      reject("Not available")
    })
  }

  returnMedia() {
    return new Promise((resolve, reject) => {
      if (!this._available) {
        setTimeout(() => {
          this._available = true;
          resolve();
        }, 1000)
        return;
      }

      reject("Already returned")
    })
  }
}
const media = new Media({title: 'alice in wonderland'});

media.addRating(9);
media.addRating(8.5);
console.log(media.getRatings()); 

const test = async () => {
  const media = new Media({title: 'alice in wonderland'})
  await media.orderMedia()
  console.log( media.getAvailable()) // false
  await media.returnMedia()
  console.log(media.getAvailable()) // true
}

// test()



class Book extends Media {
  constructor(props) {
    super(props);
    if(!props.hasOwnProperty('author'))
      throw 'author not passed!';
    if(typeof props.author !== 'string') {
      throw 'author passed is not string!'
    }
    if(!props.hasOwnProperty('pages'))
      throw 'pages not passed!';
    if(typeof props.pages !== 'number') {
      throw 'pages passed is not number!'
    }
    this._author = capitalizeSentence(props.author);
    this._pages = props.pages;
  }
  getAuthor() {
    return this._author;
  }
  getPages() {
    return this._pages;
  }

  orderBook() { //unikam powtórzeń kodu
    return this.orderMedia();
  }

  returnBook() { //unikam powtórzeń kodu
    return this.returnMedia();
  }
}

const test2 = async () => {
  const book = new Book({
    title: "alice's adventures in wonderland",
    author: 'lewis carroll',
    pages: 136
  })

  console.log(book.getTitle()) // "Alice's Adventures In Wonderland"
  console.log(book.getRatings()) // []
  console.log(book.getAvailable()) // true
  console.log(book.getAuthor()) // 'Lewis Carroll'
  console.log(book.getPages()) // 136

  book.addRating(9)
  book.addRating(8.5)
  console.log(book.getRatings()) // [9, 8.5]

  await book.orderBook()
  console.log(book.getAvailable()) // false

  await book.returnBook()
  console.log(book.getAvailable()) // true
}

// test2()

class Movie extends Media {
  constructor(props) {
    super(props);
    if(!props.hasOwnProperty('director'))
      throw 'director not passed!';
    if(typeof props.director !== 'string') {
      throw 'director passed is not string!'
    }
    if(!props.hasOwnProperty('length'))
      throw 'length not passed!';
    if(typeof props.length !== 'number') {
      throw 'length passed is not number!'
    }
    this._director = capitalizeSentence(props.director);
    this._length = props.length;
  }
  getDirector() {
    return this._director;
  }
  getLength() {
    return this._length;
  }

  orderMovie() { //unikam powtórzeń kodu
    return this.orderMedia();
  }

  returnMovie() { //unikam powtórzeń kodu
    return this.returnMedia();
  }
}

const test3 = async () => {
  const movie = new Movie({
    title: "alice in wonderland",
    director: 'tim burton',
    length: 108
  })

  console.log(movie.getTitle()) // 'Alice In Wonderland'
  console.log(movie.getRatings()) // []
  console.log(movie.getAvailable()) // true
  console.log(movie.getDirector()) // 'Tim Burton'
  console.log(movie.getLength()) // 108

  movie.addRating(9)
  movie.addRating(8.5)
  console.log(movie.getRatings()) // [9, 8.5]

  await movie.orderMovie()
  console.log(movie.getAvailable()) // false

  await movie.returnMovie()
  console.log(movie.getAvailable()) // true
}

// test3()

const addToLibrary = (props) => {
  if(!props.hasOwnProperty('title') || typeof props.title !== 'string') {
    console.log("Wrong title");
    return undefined;
  }
  let media;
  switch(props.type) {
    case "book": 
      if(!props.hasOwnProperty('author') || typeof props.author !== 'string') {
        console.log("Wrong author");
        return undefined;
      }
      if(!props.hasOwnProperty('pages') || typeof props.pages !== 'number') {
        console.log("Wrong pages");
        return undefined;
      }
      media = new Book(props)
      libraryStore.push(media)
      return media;
    case "movie": 
      if(!props.hasOwnProperty('director') || typeof props.director !== 'string') {
        console.log("Wrong director");
        return undefined;
      }
      if(!props.hasOwnProperty('length') || typeof props.length !== 'number') {
        console.log("Wrong length");
        return undefined;
      }
      media = new Movie(props)
      libraryStore.push(media)
      return media;
    default: 
      media = new Media(props);
      libraryStore.push(media)
      return media;
  }
}



// addToLibrary({
//   type: 'book',
//   title: "alice's adventures in wonderland",
//   author: 'lewis carroll',
//   pages: 136
// })
// addToLibrary({
//   type: 'movie',
//   title: "alice in wonderland",
//   director: 'tim burton',
//   length: 108
// })
// addToLibrary({
//   title: 'Media'
// })

// console.log('store = ', libraryStore)

const bulkAddToLibrary = (array) => {
  const ans = [];
  array.forEach(element => ans.push(addToLibrary(element)));
  return ans;
}

// const [book4, movie4, media4] = bulkAddToLibrary([
//   {
//     type: 'book',
//     title: "alice's adventures in wonderland",
//     author: 'lewis carroll',
//     pages: 136
//   }, 
//   {
//     type: 'movie',
//     title: "alice in wonderland",
//     director: 'tim burton',
//     length: 108
//   }, 
//   {
//     title: 'Media'
//   }
// ])

// console.log('aaaa = ', libraryStore) 
// console.log('bbbb = ', book4, movie4, media4);

const order = async (title) =>  {
  await Promise.all(libraryStore.map(async (element) => {   
    if(element.getTitle() === title) {
      await element.orderMedia();
    }
  }))
}

const bulkOrder = async (titleArray) => {
  await Promise.all(libraryStore.map(async (element) => {  
    if(titleArray.includes(element.getTitle())) {
      await element.orderMedia();
    }
  }))
}

const test5 = async () => {
  const book5 = addToLibrary({
    type: 'book',
    title: "alice's adventures in wonderland",
    author: 'lewis carroll',
    pages: 136
  })

  console.log("aaa", book5.getAvailable()) // true
  await order("Alice's Adventures In Wonderland").catch((error) => console.log("Sorry!", error))
  console.log("bbb", book5.getAvailable()) // false
  await order("Alice's Adventures In Wonderland").catch((error) => console.log("Sorry!", error)) // Sorry! Not available
}

// test5()

const test6 = async () => {
  const book = addToLibrary({
    type: 'book',
    title: "alice's adventures in wonderland",
    author: 'lewis carroll',
    pages: 136
  })
  const movie = addToLibrary({
    type: 'movie',
    title: "alice in wonderland",
    director: 'tim burton',
    length: 108
  })
  const media = addToLibrary({
    title: 'Media'
  })

  const startTime = Date.now();
  await bulkOrder(["Alice's Adventures In Wonderland", "Alice In Wonderland", "Media"])
  console.log(Date.now() - startTime) // Ok. 1000
  console.log(book.getAvailable()) // false
  console.log(movie.getAvailable()) // false
  console.log(media.getAvailable()) // false
}

// test6()