const info = document.getElementById("tasks_info__header");
const list = document.getElementById("list");
const input = document.getElementById("add_task__input");
const addTaskButton = document.getElementById("add_task__button");

let todoList = []
let isDone = []

/**
 * Function to load data from localStorage
 */
function loadData() {
    try {
        todoList = JSON.parse(window.localStorage.getItem('todoList'));
        isDone = JSON.parse(window.localStorage.getItem('isDone'));
        buildInfoHeader();
        buildList();
    } catch (error) {
        console.log(error)
    }
    
}

/**
 * Function to save data in localStorage
 */
function saveData() {
    window.localStorage.setItem('todoList', JSON.stringify(todoList));
    window.localStorage.setItem('isDone', JSON.stringify(isDone));
}

loadData();


/**
 * Clear todoList array
 */
function clearTodoList() {
    list.innerHTML = "";
    todoList.splice(0, todoList.length);
    isDone.splice(0, isDone.length);
}


/**
 * Build html code for TODO list
 */
function buildList() {
    list.innerHTML = todoList.map((value, idx) => 
    `<li class="li_task ${isDone[idx] ? 'opacity' : 'no_opacity'}">` +
    `<span class="li_span">${value}</span>` +
    `<input type="button" class="li_button_change" value="${isDone[idx] ? 'Revert' : 'Done'}" onclick="changeTask(${idx})">` +
    `<input type="button" class="li_button_remove" value="Remove" onclick="removeTask(${idx})">` +
    `</li>`
    ).join('');
}


/**
 * Build header (how many elements are in TODO list)
 */
function buildInfoHeader() {
    info.innerText = 'Todo List (' + todoList.length + ' remaining)';
}


/**
 * Function to add element to list when clicking button
 */
addTaskButton.addEventListener("click", function(e) {
    todoList.push(input.value);
    input.value = "";
    isDone.push(0);
    buildList();
    buildInfoHeader()
})


/**
 * Remove task
 */
function removeTask(idx) {
    todoList.splice(idx, 1);
    isDone.splice(idx, 1);
    buildList();
    buildInfoHeader()
}

/**
 * Change task
 */
 function changeTask(idx) {
    isDone[idx] = 1 - isDone[idx];
    buildList();
    buildInfoHeader()
}
