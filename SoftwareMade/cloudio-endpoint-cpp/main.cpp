#include <iostream>

#include "Interface/i_logger.h"
#include "EndpointStructure/endpoint.h"
#include "EndpointController/endpointfactory.h"
#include "EndpointController/endpointcontroller.h"

#include "Interface/thread.h"

#include <QApplication>
#include "captorpoll.h"
#include <QTimer>

using namespace std;
CaptorPoll* cp;

void setParam(int i);

int main(int argc, char **argv){

    QApplication application(argc, argv);

    //Get the singleton EndpointFactory
    EndpointFactory* ef = EndpointFactory::getInstance();

    //Nodes Creation
    Cloudio_Node* nodeBedroom = ef->addNode("Bedroom");
    Cloudio_Node* nodeKitchen = ef->addNode("Kitchen");

    //Objects Creation
    Cloudio_Object* objBedroomController = ef->addObject(nodeBedroom,"TempController");
    Cloudio_Object* objBedroomTemp = ef->addObject(objBedroomController,"TempMeasurement");
    Cloudio_Object* objKitchenTemp = ef->addObject(nodeKitchen,"TempMeasurement");

    //Attributes Creation
    AttributeInt* attrSetTemp = ef->addAttribute(objBedroomController, "SetTemp",Constraint::SetPoint,20, setParam);
    AttributeDouble* attrBedroomTemp = ef->addAttribute(objBedroomTemp, "BedroomTemp",Constraint::Measure,(double)9);
    AttributeDouble* attrKitchenTemp = ef->addAttribute(objKitchenTemp, "KitchenTemp",Constraint::Measure,(double)10);

    //Get the singleton EndpointController
    EndpointController* ec = EndpointController::getInstance();
    //Launch the communication to the server, to be launch after the complete construction of the structure of the endpoint
    ec->run();

    //CaptorPoll object will give a new value each 2seconds
    cp = new CaptorPoll(attrKitchenTemp,attrBedroomTemp);

    return QApplication::exec();

}

void setParam(int i){
    cp->setSetPointTemp(i);
}

//Theses tests can't be executed anymore since some of the Log::printD() were erase from the tested functions
//and some of the functions that the tests use are now private.

/*
//TEST 5
void callback_test(int i);
void mainThread();

int main(int argc, char **argv){
    //SERIALISATION JSON

    EndpointFactory* ef = EndpointFactory::getInstance();

    Cloudio_Node* node1 = ef->addNode("Node1");
    Cloudio_Object* object3 = ef->addObject(node1,"object3");
    Cloudio_Object* object1 = ef->addObject(node1,"object1");
    Cloudio_Object* object2 = ef->addObject(node1,"object2");
    Cloudio_Object* object1_1 = ef->addObject(object1,"object1_1");
    AttributeInt* attribute1 = ef->addAttribute(object1, "Attribute1",Constraint::SetPoint,0, callback_test);
    AttributeInt* attribute1_1 = ef->addAttribute(object1_1, "Attribute 1.1",Constraint::Parameter,0, callback_test);
    AttributeInt* attribute20 = ef->addAttribute(object2, "Attribute 20",Constraint::Measure,0);
    AttributeInt* attribute3 = ef->addAttribute(object3, "Attribute 3",Constraint::StaticAttribute,0);
    AttributeInt* attribute21 = ef->addAttribute(object2, "Attribute 21",Constraint::SetPoint,0, callback_test);

    Cloudio_Node* node2 = ef->addNode("Node2");
    Cloudio_Object* object4 = ef->addObject(node2,"object4");
    Cloudio_Object* object5 = ef->addObject(node2,"object5");
    AttributeInt* attribute4 = ef->addAttribute(object4, "Attribute 4",Constraint::SetPoint,0, callback_test);

    EndpointController* ec = EndpointController::getInstance();
    ec->run();
    mainThread();
}

void mainThread(){
    while(1){
        //For example launch a timer and poll the measurment when timeout, or put a delay function
        //If the measurement is different enough from the last,
        //Call function ec->setAttributeValue(...), it will send the change to the server
    }

}

void callback_test(int i){
    //What to do when the value of the attribute changes
    Log::printD("Callback sent");
}
*/
/*
//TEST 4
void callback_test(int i);
void mainThread();

int main(){
    //TEST 4 : test functionnalities of the Factory and Thread of Controller

    EndpointFactory* ef = EndpointFactory::getInstance();
    Node* node1 = ef->addNode("Node1");
    Cloudio_Object* object1 = ef->addObject(node1,"object1");
    Cloudio_Object* object2 = ef->addObject(node1,"object2");
    AttributeInt* attribute1 = ef->addAttribute(object1, "Attribute",Constraint::SetPoint,0, callback_test);

    EndpointController* ec = EndpointController::getInstance();
    Log::printD(ec->getEndpoint()->getUuid());
    ec->getEndpoint()->getAttribute(attribute1->getUuid())->displayUuid();
    ec->run();

    //Thread* mainThread = ResourceFactory::getInstance()->createThread();


    while(1){
        mainThread();
        attribute1->setValue(1);
    }
    return 0;
}

void mainThread(){
    while(true){
        Log::printD("I'm the main, I'm angry, very angry");
            Sleep( 5000 );
    }
}

void callback_test(int i){
    Log::printD("Callback sent");
}
*/


//TEST 3
/*
void callback_test(string s);
void callback_test(int i);
int main(){

    //Test 3 : Test callback

    Log::printD("Hello, start Test 3");

    //Function pointer
    void (*callbackInt_ptr)(int) = &callback_test;
    void (*callbackString_ptr)(string) = &callback_test;

    //Different object for the test
    AttributeBool* status = new AttributeBool("Status",Constraint::Status,true);

    Log::printD("Normally message to prevent that the callback method is useless");
    AttributeInt* temperature = new AttributeInt("temperature",Constraint::Measure,10, callbackInt_ptr );

    Log::printD("Normally message to prevent that the Attribute has no callback");
    AttributeFloat* setPoint = new AttributeFloat("setPoint",Constraint::SetPoint,15);

    Log::printD("Try to callback");
    AttributeString* setPoint2 = new AttributeString("setPoint2",Constraint::SetPoint,"Hi", callbackString_ptr);
    setPoint2->setValue("Callback was sent");    

    return 0;
}

void callback_test(string s){
        Log::printD(s);
}
void callback_test(int i){

}

*/

//TEST 2

/*
int main(){

    //Test 2 : Test Topic automatic implementation with class uuid and check construction order

    //Construction order is important to have automatic build of topic (called here uuid)

    Log::printD("Hello, start Test 2");

    //Different object for the test
    Endpoint* endpoint = new Endpoint();
    Node* node1 = new Node("node1");
    Cloudio_Object* object1 = new Cloudio_Object("object1");
    AttributeBool* status = new AttributeBool("Status",Constraint::Status,true);
    AttributeInt* temperature = new AttributeInt("temperature",Constraint::Measure,10);
    AttributeFloat* setPoint = new AttributeFloat("setPoint",Constraint::SetPoint,15);
    Cloudio_Object* object2 = new Cloudio_Object("object2");
    Cloudio_Object* object2_2 = new Cloudio_Object("object2_2");
    Cloudio_Object* object2_2_2 = new Cloudio_Object("object2_2_2");
    Cloudio_Object* object3 = new Cloudio_Object("object3");
    AttributeBool* status2 = new AttributeBool("Status2",Constraint::Status,true);
    AttributeInt* temperature2 = new AttributeInt("temperature2",Constraint::Measure,10);
    AttributeFloat* setPoint2 = new AttributeFloat("setPoint2",Constraint::SetPoint,15);

    //Forget to build the node before inserting it to an Endpoint
    Log::printD("Normally message to prevent that the node wasn't in an Endpoint");
    node1->addObject(object1);

    endpoint->addNode(node1);

    //Forget to add the object before the line
    Log::printD("Normally message to prevent that the object wasn't in a node");
    object2->addObject(object2_2);

    //Continue building the Node
    node1->addObject(object2);
    node1->addObject(object3);
    object2->addObject(object2_2);
    object2->addAttribute(status2);
    object2_2->addObject(object2_2_2);
    object2_2_2->addAttribute(temperature2);
    object2_2_2->addAttribute(setPoint2);


    //Build the Node
    node1->addObject(object1);
    object1->addAttribute(status);
    object1->addAttribute(temperature);
    object1->addAttribute(setPoint);

    //print UUid
    node1->displayUuid();
    temperature->displayUuid();

    object1->displayUuid();
    object2->displayUuid();
    object2_2->displayUuid();
    object2_2_2->displayUuid();

    temperature2->displayUuid();
    status2->displayUuid();

    Log::printD("Test getObject from Endpoint");
    Cloudio_Object* ptr = endpoint->getObject(object2_2_2->getUuid());
    ptr->displayUuid();

    Log::printD("Test getAttribute from Endpoint");
    Attribute* ptrA = endpoint->getAttribute(temperature2->getUuid());
    ptrA->displayUuid();

    return 0;
}
*/

//TEST 1
/*

int main()
{

    //Test 1 : Creation of basic objects (Endpoint, Node, Objects, Attribute) and Logger

    Log::printD("Hello, start Test 1");
    Endpoint* endpoint = new Endpoint();
    Node* node1 = new Node("CertainlyANordicThingySoItWork");
    Cloudio_Object* object1 = new Cloudio_Object("Thermometer");
    AttributeBool* status = new AttributeBool("Status",Constraint::Status,true);
    AttributeInt* temperature = new AttributeInt("temp",Constraint::Measure,10);
    AttributeFloat* setPoint = new AttributeFloat("setPoint",Constraint::SetPoint,15);
    Node* node2 = new Node("AMicrochipSoItDontWork");
    Cloudio_Object* object2 = new Cloudio_Object("Thermometer");
    Cloudio_Object* object2_1 = new Cloudio_Object("Thermometer");
    Cloudio_Object* object2_2 = new Cloudio_Object("subThermometer");
    Cloudio_Object* object3 = new Cloudio_Object("UselessCaptor");
    AttributeBool* status2 = new AttributeBool("Status",Constraint::Status,true);
    AttributeInt* temperature2 = new AttributeInt("temp",Constraint::Measure,10);
    AttributeFloat* setPoint2 = new AttributeFloat("setPoint",Constraint::SetPoint,15);

    endpoint->addNode(node1);
    endpoint->addNode(node2);

    //Build the first Node
    node1->addObject(object1);
    object1->addAttribute(status);
    object1->addAttribute(temperature);
    object1->addAttribute(setPoint);

    //setValue for temperature and status shouldn't work
    Log::printD("Text should be print for setValue and status");
    setPoint->setValue(15);
    status->setValue(false);
    temperature->setValue(12);

    //Build the second Node
    node2->addObject(object2);
    node2->addObject(object3);
    object2->addObject(object2_2);
    object2->addAttribute(status2);
    object2_2->addAttribute(temperature2);
    object2_2->addAttribute(setPoint2);

    //same name so it shouldn't work
    Log::printD("Text with same name found :");
    node2->addObject(object2_1);

    //Add Attribute status shouldn't work becase his parent is already set
    Log::printD("Text with has already a parent should be print");
    object2->addAttribute(status);

    //Test the remove operation
    endpoint->removeNode(node1);
    node2->removeObject(object3);
    object2->removeObject(object2_2);
    object2->removeAttribute(status2);

    //Remove a non-existant object in the "tree"
    Log::printD("Text with object not found should be print");
    object2->removeObject(object2_1);


    return 0;
}
*/

