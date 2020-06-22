#include "PySubscriptionService.hpp"
#include "Arp/System/Commons/Logging.h"
#include "util/docMacros.hpp"
#include "util/arg.hpp"
#include "PyDataAccessService.hpp"
namespace PythonArp::PySubscriptionService
{

#define SUBSCRIPTION_CLOSEDREALTIME     (int32)SubscriptionKind::ClosedRealTime
#define SUBSCRIPTION_DIRECTREAD         (int32)SubscriptionKind::DirectRead
#define SUBSCRIPTION_HIGHPERFORMANCE    (int32)SubscriptionKind::HighPerformance
#define SUBSCRIPTION_REALTIME           (int32)SubscriptionKind::RealTime
#define SUBSCRIPTION_RECORDING          (int32)SubscriptionKind::Recording

static char Subcription__ClassName[] = "SubscriptionService";



/* -------------------------------------------------------------------------- */
/*                              Subscription_obj                              */
/* -------------------------------------------------------------------------- */
typedef struct
{   PyObject_HEAD

    ISubscriptionService::Ptr p_ISubscriptionService;
    SubscriptionKind kind = SubscriptionKind::None;
    uint32 subscription_id=0;
    uint64 sampleRate=0;
    uint16 recordCount = 10;
    std::list<String> *VariablesAdd = nullptr;
    std::list<VariableInfo> *VariableInfos = nullptr;
    std::list<VariableInfo> *TimeStampedVariableInfos= nullptr;
    std::list<std::list<VariableInfo>> *RecordInfos=nullptr;

    bool GetInfosRequires[3]={true,true,true};
} Subscription_obj;

//forword
static PyObject* Subcription_CreateSubscription (Subscription_obj *self,PyObject* args, PyObject* kw);
static PyObject* Subcription__DeleteSubscription (Subscription_obj *self);



static DataAccessError _GetVariableInfos(Subscription_obj* self)
{
    if (!self->VariableInfos)
    {
        self->VariableInfos = new std::list<VariableInfo>();
    }
    return self->p_ISubscriptionService->GetVariableInfos(self->subscription_id,ISubscriptionService::GetVariableInfosVariableInfoDelegate::create([&](IRscReadEnumerator<VariableInfo>& ReadEnumerator)
    {
    self->VariableInfos->clear();
    uint count = ReadEnumerator.BeginRead();
    for (uint i = 0;i<count;i++)
    {
        VariableInfo current;
        ReadEnumerator.ReadNext(current);
        self->VariableInfos->emplace_back(current);
    }
    ReadEnumerator.EndRead();
    }));
}
static DataAccessError _GetTimeStampedVariableInfos(Subscription_obj* self)
{
    if (!self->TimeStampedVariableInfos)
    {
        self->TimeStampedVariableInfos = new std::list<VariableInfo>();
    }
    return self->p_ISubscriptionService->GetTimeStampedVariableInfos(self->subscription_id,ISubscriptionService::GetTimeStampedVariableInfosVariableInfoDelegate::create([&](IRscReadEnumerator<VariableInfo>& ReadEnumerator){
        self->TimeStampedVariableInfos->clear();
        uint count = ReadEnumerator.BeginRead();
        for (uint i = 0;i<count;i++)
        {
            VariableInfo current;
            ReadEnumerator.ReadNext(current);
            self->TimeStampedVariableInfos->emplace_back(current);
        }
        ReadEnumerator.EndRead();
    }));
}
static DataAccessError _GetRecordInfos(Subscription_obj* self)
{

    if (!self->RecordInfos)
    {
        self->RecordInfos = new std::list<std::list<VariableInfo>>();
    }
    return self->p_ISubscriptionService->GetTimeStampedVariableInfos(self->subscription_id,ISubscriptionService::GetTimeStampedVariableInfosVariableInfoDelegate::create([&](IRscReadEnumerator<VariableInfo>& ReadEnumerator){
        self->RecordInfos->clear();
        uint count = ReadEnumerator.BeginRead();
        std::list<VariableInfo> current_subVector;
        VariableInfo current;
        for (uint i = 0;i<count;i++)
        {
            ReadEnumerator.ReadNext(current);
            if (strcmp(current.Name.CStr(),"timestamp")==0 && i>0)
            {
                self->RecordInfos->push_back(current_subVector);
                current_subVector.clear();
            }
            current_subVector.push_back(current);
            if (i == count-1)
            {
                self->RecordInfos->push_back(current_subVector);
            }
        }
        ReadEnumerator.EndRead();
    }));
}

/* --------------------------------- __doc__ -------------------------------- */
ArpPyDoc_STRVAR(Subcription__doc__,
R"(
SubscriptionService...
)");


/* --------------------------------- dealloc -------------------------------- */
static void _Subscription_dealloc(Subscription_obj* self) 
{
    if (self->VariablesAdd)
    {
        delete self->VariablesAdd;
    }
    if (self->VariableInfos)
    {
        delete self->VariableInfos;
    }
    if(self->TimeStampedVariableInfos)
    {
        delete self->TimeStampedVariableInfos;
    }
    if(self->RecordInfos)
    {
        delete self->RecordInfos;
    }
    Subcription__DeleteSubscription(self);
    self->p_ISubscriptionService.reset();
    Py_TYPE(self)->tp_free(self);
}



/* -------------------------------- __init__ -------------------------------- */
static int _SubscriptionService___init__ (Subscription_obj *self,PyObject* args, PyObject* kw)
{
    self->p_ISubscriptionService = ServiceManager::GetService<ISubscriptionService>();
    self->VariablesAdd = new std::list<String>();
    if((!PythonArp::util::argParse::_Py_hadNoPositional(args)) or (!PythonArp::util::argParse::_Py_hasNoKeywords(kw)))
    {
        Subcription_CreateSubscription(self,args,kw);
        if(PyErr_Occurred())
        {
            return -1;
        }
    }
    return 0;
}


/* ---------------------------  CreateSubscription -------------------------- */
#define _SUBSCRIPTION_CREATESUBSCRIPTION_METHODDEF \
{"CreateSubscription", (PyCFunction)Subcription_CreateSubscription, METH_VARARGS | METH_KEYWORDS, Subcription_CreateSubscription__doc__},
ArpPyDoc_STRVAR(Subcription_CreateSubscription__doc__,
"Method to create subscription");
static PyObject* Subcription_CreateSubscription (Subscription_obj *self,PyObject* args, PyObject* kw)
{
        static const char *kwList[] = {"kind", "recordCount", NULL};
        int recordCount = 10;
        int kind = 0;

        if (!util::argParse::xPyArg_ParseTupleAndKeywords(args, kw, "i|i",(char **) kwList, &kind, &recordCount))
        {
            return NULL;
        }

        if (kind<1 or kind >5)
        {
            PyErr_SetString(PyExc_TypeError, "Wrong Subscription kind !");
            return NULL;
        }

        if (kind == (int)SubscriptionKind::Recording)
        {
            if(recordCount == 10)
            {
                self->subscription_id =  self->p_ISubscriptionService->CreateSubscription((SubscriptionKind)kind);
            }
            else
            {
                self->subscription_id =  self->p_ISubscriptionService->CreateRecordingSubscription(recordCount);
            }
        }
        else
        {
            self->subscription_id =  self->p_ISubscriptionService->CreateSubscription((SubscriptionKind)kind);
        }
        
        self->kind = (SubscriptionKind)kind;
        self->recordCount = recordCount;

        return PyLong_FromUnsignedLong(self->subscription_id);
}

/* -------------------------- RecreateSubscription -------------------------- */
#define _SUBSCRIPTION_RECREATESUBSCRIPTION_METHODDEF \
{"RecreateSubscription",   (PyCFunction)Subcription_RecreateSubscription,METH_NOARGS,Subcription_RecreateSubscription__doc__},
ArpPyDoc_STRVAR(Subcription_RecreateSubscription__doc__,
"Method to recreate subscription");
static PyObject* Subcription_RecreateSubscription (Subscription_obj *self)
{
    if (self->kind==SubscriptionKind::None)
    {
        PyErr_SetString(PyExc_TypeError,"Bad operation,there is no setting parameters");
        return NULL;
    }

    if (self->kind ==SubscriptionKind::Recording)
    {
        if(self->recordCount == 10)
        {
            self->subscription_id =  self->p_ISubscriptionService->CreateSubscription(self->kind);
        }
        else
        {
            self->subscription_id =  self->p_ISubscriptionService->CreateRecordingSubscription(self->recordCount);
        }
    }
    else
    {
        self->subscription_id =  self->p_ISubscriptionService->CreateSubscription(self->kind);
    }

    for (auto &var: *self->VariablesAdd)
    {
        self->p_ISubscriptionService->AddVariable(self->subscription_id,var);
    }

    return PyLong_FromUnsignedLong(self->subscription_id);
}




/* ---------------------------- GetSubscriptionID --------------------------- */
#define _SUBSCRIPTION_GETSUBSCRIPTION_METHODDEF \
{"GetSubscriptionID",   (PyCFunction)Subcription_GetSubscriptionID,METH_NOARGS,Subcription_GetSubscriptionID__doc__},
ArpPyDoc_STRVAR(Subcription_GetSubscriptionID__doc__,
"Method to get current subscription id");
static PyObject* Subcription_GetSubscriptionID (Subscription_obj *self)
{
    return PyLong_FromLong(self->subscription_id);
}


/* ---------------------------- SetSubscriptionID --------------------------- */
#define _SUBSCRIPTION_SETSUBSCRIPTION_METHODDEF \
{"SetSubscriptionID",   (PyCFunction)Subcription_SetSubscriptionID,METH_VARARGS,Subcription_SetSubscriptionID__doc__},
ArpPyDoc_STRVAR(Subcription_SetSubscriptionID__doc__,
"Method to set current subscription id, notice this is not a common usage ! usually for internal test");
static PyObject* Subcription_SetSubscriptionID (Subscription_obj *self,PyObject* args)
{
    unsigned long newID =0;
    if(!PyArg_ParseTuple(args,"k",&newID))
    {
        return NULL;
    }
    self->subscription_id = newID;
    Py_RETURN_NONE;
}



/* ------------------------------- AddVariable ------------------------------ */
#define _SUBSCRIPTION_ADDVARIABLE_METHODDEF \
{"AddVariable", (PyCFunction)Subcription_AddVariable, METH_VARARGS | METH_KEYWORDS, Subcription_AddVariable__doc__},
ArpPyDoc_STRVAR(Subcription_AddVariable__doc__,
R"(
The added variable is stored in a internal container and will be subscribed after 
calling 'Subscribe' ,If the subscription has already been subscribed, it is necessary 
to call 'Resubscribe' to subscribe the new added variable finally.

If the same full variable name is added multiple times, the old variable will be 
overridden. In case, a variable name is invalid or doesn't exists a specific error 
code will be returned ,on success the code "None" of the added variable will be 
returned. A variable which doesn't returned with "None" won't be added to the 
subscription and won't be subscribed.

A single array element can added with its index in brackets e.g.:
    'ComponentName-1/ProgramName-1.Array_Name[index]'
Or a rage of an array can added with tow indexes separated with a colon in brackets e.g.:
    'ComponentName-1/ProgramName-1.Array_Name[StartIndex:EndIndex]'
If an array variable is added without a variable specification,the entire array 
will be added to the subscription.

Returns "None" on success.

@KeywordsParam variables : str,list or tuple of variables' name
@KeywordsParam prefix    : variables prefix string.(optional)
@return Dict             : DataAccessError
)");
static PyObject* Subcription_AddVariable (Subscription_obj *self,PyObject* args, PyObject* kw)
{
    static const char *kwList[] = {"variables", "prefix", NULL};
    PyObject *t_seq, *t_item, *PyO_variables;
    const char *prefix = NULL;
    if (!util::argParse::xPyArg_ParseTupleAndKeywords(args, kw, "O|s",(char **) kwList, &PyO_variables, &prefix))
    {
        return NULL;
    }

    if (self->subscription_id ==0)
    {
        PyErr_SetString(PyExc_RuntimeError,"No subcription created yet !");
        return NULL;
    }

    std::list<String> varNames;
    PyObject* ret = PyDict_New();
    //parse varNames
    do
    {
        if (PyUnicode_Check(PyO_variables))
        {

            varNames.push_back(PyUnicode_AsUTF8(PyO_variables));
            break;
        }
        else if (PyTuple_Check(PyO_variables) or PyList_Check(PyO_variables))
        {
            t_seq = PyObject_GetIter(PyO_variables);
            while ((t_item = PyIter_Next(t_seq)))
            {
                if (PyUnicode_Check(t_item))
                {
                    varNames.push_back(PyUnicode_AsUTF8(t_item));
                    Py_XDECREF(t_item);
                }
                else
                {
                    Py_XDECREF(t_item);
                    Py_XDECREF(t_seq);
                    PyErr_SetString(PyExc_TypeError, "all items must be str");
                    return NULL;
                }
            }
            Py_XDECREF(t_seq);
            break;
        }
        else
        {
            PyErr_SetString(PyExc_TypeError, "Variables should be tuple, List or Str !");
            return NULL;
        }
    } while (0);
    //add prefix
    if (prefix != NULL)
    {
        do
        {
            String s_prefix = prefix;
            if (s_prefix.IsEmpty())
                break;
            for (auto &vn : varNames)
                vn = s_prefix + vn;
        } while (0);
    }

    self->p_ISubscriptionService->AddVariables(self->subscription_id,ISubscriptionService::AddVariablesVariableNamesDelegate::create([&](IRscWriteEnumerator<RscString<512>>& WriteEnumerator)
        {
            WriteEnumerator.BeginWrite(varNames.size());
            for (auto &name : varNames) WriteEnumerator.WriteNext(name);
            WriteEnumerator.EndWrite();
        }),ISubscriptionService::AddVariablesResultDelegate::create([&](IRscReadEnumerator<DataAccessError>& ReadEnumerator)
        {
            size_t count = ReadEnumerator.BeginRead();
            
            std::list<String>::const_iterator iter_VarName = varNames.begin();
            for(size_t i=0;i <count;i++,iter_VarName++)
            {
                DataAccessError current;
                ReadEnumerator.ReadNext(current);
                
                //if(current == DataAccessError::None)
                //{
                    self->VariablesAdd->emplace_back(*iter_VarName);
                //}

                PyObject *tmp = PyUnicode_FromString(Enum<DataAccessError>(current).ToString().CStr());
                PyDict_SetItemString(ret,iter_VarName->CStr(),tmp);
                Py_XDECREF(tmp);
            }
            ReadEnumerator.EndRead();
        }));
    return ret;
}

/* ----------------------------- RemoveVariable ----------------------------- */
#define _SUBSCRIPTION_REMOVEVARIABLE_METHODDEF \
{"RemoveVariable", (PyCFunction)Subcription_RemoveVariable, METH_VARARGS | METH_KEYWORDS, Subcription_RemoveVariable__doc__},
ArpPyDoc_STRVAR(Subcription_RemoveVariable__doc__,
R"(
Removes the variable with the specific variable name from the subscription.
Removes the variable that compare equal to the given variable name, from the
internal variable list. If the subscription has already been subscribed,
it is necessary to call 'Resubscribe' to remove the given variable from the 
internal created buffer.

Returns "None" on success.

@KeywordsParam variables : str,list or tuple of variables' name
@KeywordsParam prefix    : variables prefix string.(optional)
@return Dict             : DataAccessError
)");
static PyObject* Subcription_RemoveVariable (Subscription_obj *self,PyObject* args, PyObject* kw)
{
    static const char *kwList[] = {"variables", "prefix", NULL};
    PyObject *t_seq, *t_item, *PyO_variables;
    const char *prefix = NULL;
    if (!util::argParse::xPyArg_ParseTupleAndKeywords(args, kw, "O|s",(char **) kwList, &PyO_variables, &prefix))
    {
        return NULL;
    }
    if (self->subscription_id ==0)
    {
        PyErr_SetString(PyExc_RuntimeError,"No subcription created yet !");
        return NULL;
    }
    std::list<String> varNames;
    std::list<DataAccessError> dataAccessErrors;
    PyObject* ret = PyDict_New();
    //parse varNames
    do
    {
        if (PyUnicode_Check(PyO_variables))
        {
            varNames.push_back(PyUnicode_AsUTF8(PyO_variables));
            break;
        }
        else if (PyTuple_Check(PyO_variables) or PyList_Check(PyO_variables))
        {
            t_seq = PyObject_GetIter(PyO_variables);
            while ((t_item = PyIter_Next(t_seq)))
            {
                if (PyUnicode_Check(t_item))
                {
                    varNames.push_back(PyUnicode_AsUTF8(t_item));
                    Py_XDECREF(t_item);
                }
                else
                {
                    Py_XDECREF(t_item);
                    Py_XDECREF(t_seq);
                    PyErr_SetString(PyExc_TypeError, "all items must be str");
                    return NULL;
                }
            }
            Py_XDECREF(t_seq);
            break;
        }
        else
        {
            PyErr_SetString(PyExc_TypeError, "Variables should be tuple, List or Str !");
            return NULL;
        }
    } while (0);
    //add prefix
    if (prefix != NULL)
    {
        do
        {
            String s_prefix = prefix;
            if (s_prefix.IsEmpty())
                break;
            for (auto &vn : varNames)
                vn = s_prefix + vn;
        } while (0);
    }

    std::list<String>::const_iterator iter_VarName = varNames.begin();
    for (auto &var:varNames)
    {
        DataAccessError tmpError= self->p_ISubscriptionService->RemoveVariable(self->subscription_id,var);
        if (tmpError == DataAccessError::None)
        {
            for(std::list<String>::iterator iter=self->VariablesAdd->begin();iter!=self->VariablesAdd->end();iter++)
            {
                if(iter->Compare(var)==0)
                {
                    self->VariablesAdd->erase(iter);
                    break;
                }
            }
        }

        PyObject *tmp = PyUnicode_FromString(Enum<DataAccessError>(tmpError).ToString().CStr());
        PyDict_SetItemString(ret,iter_VarName->CStr(),tmp);
        Py_XDECREF(tmp);
        iter_VarName++;
    }
    return ret;
}



/* -------------------------------- Subscribe ------------------------------- */
#define _SUBSCRIPTION_SUBSCRIBE_METHODDEF \
{"Subscribe", (PyCFunction)Subcription_Subscribe, METH_VARARGS, Subcription_Subscribe__doc__},
ArpPyDoc_STRVAR(Subcription_Subscribe__doc__,
R"(
Subscribes the subscription
All previously added variables including in the given subscription will be subscribed. Internally
the variables are separated in the respective tasks, a buffer for each task will be created and
connected to the task executed event. At this point the task will copy the selected variable data
into the task buffer (excluded subscriptions from kind "SUBSCRIPTION_DIRECTREAD").
How often the task stores the data to the buffer depends on the task cycle time and the
configured subscription sample rate.

Calling this method on a already subscribed subscription has no effect, even if new
variables have been added or removed. To make variable modification effective, use
"Resubscribe". Calling this method while the subscription is in the state "Unsubscribed", 
because "Unsubscribe" has been called, will only connect the already constructed buffer to the 
respective tasks and will set the given sampleRate. Compare to the first and initial call of 
this method, this call cost more less time because the buffer are already created. 
This also means that variable modification which have been done after the first call of "Subscribe",
have also no effect. At this point it is also necessary to call "Resubscribe" .

Returns "None" on success.

@PositionalParam        : sampleRate.(micro-seconds)
@return Dict            : DataAccessError

)");
static PyObject* Subcription_Subscribe (Subscription_obj *self,PyObject* args)
{
    unsigned long long sampleRate = 0;
    if(!PyArg_ParseTuple(args,"K",&sampleRate))
    {
        return NULL;
    }
    if (self->subscription_id ==0)
    {
        PyErr_SetString(PyExc_RuntimeError,"No subcription created yet !");
        return NULL;
    }

    DataAccessError ret = self->p_ISubscriptionService->Subscribe(self->subscription_id,(uint64)sampleRate);
    self->sampleRate = (uint64)sampleRate;

    self->GetInfosRequires[0]= true;self->GetInfosRequires[1]= true;self->GetInfosRequires[2]= true;

    return PyUnicode_FromString(Enum<DataAccessError>(ret).ToString().CStr());
}

/* ------------------------------- Resubscribe ------------------------------ */
#define _SUBSCRIPTION_RESUBSCRIBE_METHODDEF \
{"Resubscribe", (PyCFunction)Subcription_Resubscribe, METH_VARARGS, Subcription_Resubscribe__doc__},
ArpPyDoc_STRVAR(Subcription_Resubscribe__doc__,
R"(
Resubscribes the subscription

Resubscribes the subscription, which will trigger a completely rebuild process of
the whole subscription, including previously done variable modification which have been
done after the first call of "Subscribe".
It destroys the internal buffer and subscribes the subscription again
(for further information see "Subscribe").
Note that the subscription is not able to collect data from the variables, while the
resubscribe process is in progress.

This method has only an effect if the given subscription is currently subscribed,
otherwise nothing will happen.

Returns "None" on success.

@PositionalParam        : sampleRate.(micro-seconds)(optional)
@return Dict            : DataAccessError
)");
static PyObject* Subcription_Resubscribe (Subscription_obj *self,PyObject* args)
{
    if (self->subscription_id ==0)
    {
        PyErr_SetString(PyExc_RuntimeError,"No subcription created yet !");
        return NULL;
    }
    DataAccessError ret = DataAccessError::None;
    if(PythonArp::util::argParse::_Py_hadNoPositional(args))
    {
        ret = self->p_ISubscriptionService->Resubscribe(self->subscription_id,self->sampleRate);
    }
    else
    {
        unsigned long long sampleRate = 0;
        if(!PyArg_ParseTuple(args,"K",&sampleRate))
        {
            return NULL;
        }
        ret = self->p_ISubscriptionService->Resubscribe(self->subscription_id,(uint64)sampleRate);
        self->sampleRate = (uint64)sampleRate;
    }
    self->GetInfosRequires[0]= true;self->GetInfosRequires[1]= true;self->GetInfosRequires[2]= true;
    return PyUnicode_FromString(Enum<DataAccessError>(ret).ToString().CStr());
}


/* ------------------------------- Unsubscribe ------------------------------ */
#define _SUBSCRIPTION_UNSUBSCRIBE_METHODDEF \
{"Unsubscribe", (PyCFunction)Subcription_Unsubscribe, METH_NOARGS, Subcription_Unsubscribe__doc__},
ArpPyDoc_STRVAR(Subcription_Unsubscribe__doc__,
R"(
Unsubscribes the subscription

Unsubscribes the subscription from all task executed events. The subscription
data are still exist and could be get by the respective read-methods. To
subscribe the subscription again, call "Subscribe".

This method has only an effect if the given subscription is currently subscribed,
otherwise nothing will happen.

Returns "None" on success.
)");
static PyObject* Subcription_Unsubscribe (Subscription_obj *self)
{
    if (self->subscription_id ==0)
    {
        PyErr_SetString(PyExc_RuntimeError,"No subcription created yet !");
        return NULL;
    }
    DataAccessError ret = self->p_ISubscriptionService->Unsubscribe(self->subscription_id);
    return PyUnicode_FromString(Enum<DataAccessError>(ret).ToString().CStr());
}

/* --------------------------- DeleteSubscription --------------------------- */
#define _SUBSCRIPTION_DELETESUBSCRIPTION_METHODDEF \
{"_DeleteSubscription", (PyCFunction)Subcription__DeleteSubscription, METH_NOARGS, Subcription_DeleteSubscription__doc__},
ArpPyDoc_STRVAR(Subcription_DeleteSubscription__doc__,
"Method to DeleteSubscription,this method will be called when class dealloc ,user don't need to call this normally");
static PyObject* Subcription__DeleteSubscription (Subscription_obj *self)
{
    DataAccessError ret = self->p_ISubscriptionService->DeleteSubscription(self->subscription_id);
    self->subscription_id = 0;
    return PyUnicode_FromString(Enum<DataAccessError>(ret).ToString().CStr());
}

/* ------------------------------- ReadValues ------------------------------- */
#define _SUBSCRIPTION_READVALUES_METHODDEF \
{"ReadValues", (PyCFunction)Subcription_ReadValues, METH_NOARGS, Subcription_ReadValues__doc__},
ArpPyDoc_STRVAR(Subcription_ReadValues__doc__,
R"(
Read the data from the subscription

Note that this values doesn't contain timestamps! If the timestamp is
needed use the function "ReadTimeStampedValues" instead.

The read data may contain null values (None) if the read call was executed
before the tasks initially have written the data.

return : (DataAccessError,{"variableName1":value,"variableName2":value ...})

)");
static PyObject* Subcription_ReadValues (Subscription_obj *self)
{
    if (self->subscription_id ==0)
    {
        PyErr_SetString(PyExc_RuntimeError,"No subcription created yet !");
        return NULL;
    }

    if (self->GetInfosRequires[0])
    {
        _GetVariableInfos(self);
        self->GetInfosRequires[0]= false;
    }

    PyObject* result_dict =  PyDict_New();
    DataAccessError DAE = self->p_ISubscriptionService->ReadValues(self->subscription_id,ISubscriptionService::ReadValuesValuesDelegate::create([&](IRscReadEnumerator<RscVariant<512>>& ReadEnumerator){
    uint count = ReadEnumerator.BeginRead();
    std::list<VariableInfo>::const_iterator iter_info = self->VariableInfos->begin();
    for (uint i=0;i<count;i++,iter_info++)
    {
        RscVariant<512> current;
        ReadEnumerator.ReadNext(current);
        PyObject *tmpValue = PythonArp::PyDataAccessService::AutoTypeReadHandler(current);
        PyDict_SetItemString(result_dict,iter_info->Name.CStr(),tmpValue);
        Py_XDECREF(tmpValue);
    }
    ReadEnumerator.EndRead();
    }));
    return Py_BuildValue("NN",PyUnicode_FromString(Enum<DataAccessError>(DAE).ToString().CStr()),result_dict);
}


/* -------------------------- ReadTimeStampedValues ------------------------- */
#define _SUBSCRIPTION_READTIMESTAMPEDVALUES_METHODDEF \
{"ReadTimeStampedValues", (PyCFunction)Subcription_ReadTimeStampedValues, METH_NOARGS, Subcription_ReadTimeStampedValues__doc__},
ArpPyDoc_STRVAR(Subcription_ReadTimeStampedValues__doc__,
R"(
Read the data including timestamps from the subscription

The read data may contain null values (None) if the read call was executed
before the tasks initially have written the data.

@return : (DataAccessError,{"variableName1":(value,timestamp),"variableName2":(value,timestamp) ...})
)");
static PyObject* Subcription_ReadTimeStampedValues (Subscription_obj *self)
{
    if (self->subscription_id ==0)
    {
        PyErr_SetString(PyExc_RuntimeError,"No subcription created yet !");
        return NULL;
    }
    if (self->GetInfosRequires[1])
    {
        _GetTimeStampedVariableInfos(self);
        self->GetInfosRequires[1]= false;
    }
    PyObject* result_dict =  PyDict_New();
    DataAccessError DAE = self->p_ISubscriptionService->ReadTimeStampedValues(self->subscription_id,ISubscriptionService::ReadValuesValuesDelegate::create([&](IRscReadEnumerator<RscVariant<512>>& ReadEnumerator){
        uint count = ReadEnumerator.BeginRead();
        std::list<VariableInfo>::const_iterator iter_info = self->TimeStampedVariableInfos->begin();
        int64_t timestamp = 0;
        RscVariant<512> current;
        for (uint i=0;i<count;i++,iter_info++)
        {
            ReadEnumerator.ReadNext(current);
            if(strcmp(iter_info->Name.CStr(),"timestamp")==0)
            {
                if (current.GetType()==RscType::Int64)
                    current.CopyTo(timestamp);
                else
                    timestamp = 0;
            }
            else
            {
                PyObject* currentTuple = PyTuple_New(2);
                PyTuple_SetItem(currentTuple,0,PythonArp::PyDataAccessService::AutoTypeReadHandler(current));
                PyTuple_SetItem(currentTuple,1,PyLong_FromLongLong(timestamp));
                PyDict_SetItemString(result_dict,iter_info->Name.CStr(),currentTuple);
                Py_XDECREF(currentTuple);
            }
        }
        ReadEnumerator.EndRead();
        }));
    return Py_BuildValue("NN",PyUnicode_FromString(Enum<DataAccessError>(DAE).ToString().CStr()),result_dict);
}



/* ----------------------------- GetRecordInfos ----------------------------- */
#define _SUBSCRIPTION_GETRECORDINFOS_METHODDEF \
{"GetRecordInfos", (PyCFunction)Subcription_GetRecordInfos, METH_NOARGS, Subcription_GetRecordInfos__doc__},
ArpPyDoc_STRVAR(Subcription_GetRecordInfos__doc__,
R"(
Get the subscribed variable information as a record of the subscription

The information are provided in an array of array of variable name
The first array correspond to the number of different tasks and the 
second contains the related variable information which are related to 
the variables of this task .


@return : (DataAccessError,(TASK1("variable1","variable2"...),TASK2("variable5"...)...   ))

)");
static PyObject* Subcription_GetRecordInfos (Subscription_obj *self)
{
    if (self->subscription_id ==0)
    {
        PyErr_SetString(PyExc_RuntimeError,"No subcription created yet !");
        return NULL;
    }
    DataAccessError DAE = DataAccessError::None;
    if (self->GetInfosRequires[2])
    {
        DAE = _GetRecordInfos(self);
        self->GetInfosRequires[2]= false;
    }

    PyObject *ret = PyTuple_New(self->RecordInfos->size());
    int index_task = 0;
    for (auto &task: *self->RecordInfos)
    {
        PyObject *PYO_ITEM = PyTuple_New(task.size()-1);//ignore timestamp
        int index_item = 0;
        for (auto &item : task)
        {
            if (strcmp(item.Name.CStr(),"timestamp")==0)continue;
            
            PyTuple_SetItem(PYO_ITEM,index_item,PyUnicode_FromString(item.Name.CStr()));
            index_item++;
        }
        PyTuple_SetItem(ret,index_task,PYO_ITEM);
        index_task++;
    }

    return Py_BuildValue("NN",PyUnicode_FromString(Enum<DataAccessError>(DAE).ToString().CStr()),ret);
}



/* ------------------------------- ReadRecords ------------------------------ */
#define _SUBSCRIPTION_READRECORDS_METHODDEF \
{"ReadRecords", (PyCFunction)Subcription_ReadRecords, METH_VARARGS, Subcription_ReadRecords__doc__},
ArpPyDoc_STRVAR(Subcription_ReadRecords__doc__,
R"(
Read the data including timestamps from the subscription separated in task records.
This service function returns the plain data values from the added and subscribed 
variables including timestamps separated in task records.

<param name="count">
Number of maximum records to be copied per task. If set to zero, all available records
will be copied.

@PositionalParam        : count
@return:

(DataAccessError ,
    (   TASK1   (   CYCLE1  {"variableName1":(value,timestamp),"variableName2":(value,timestamp) ...},  
                    CYCLE2  {"variableName1":(value,timestamp),"variableName2":(value,timestamp) ...},
                    ...  
                ),
        TASK2   (   CYCLE1  {"variableName3":(value,timestamp),"variableName4":(value,timestamp) ...},
                    ...
                ),
        TASK3   (...),
        ...
    )
)

)");
static PyObject* Subcription_ReadRecords (Subscription_obj *self,PyObject* args)
{
    if (self->subscription_id ==0)
    {
        PyErr_SetString(PyExc_RuntimeError,"No subcription created yet !");
        return NULL;
    }
    unsigned short count = 0;
    DataAccessError DAE = DataAccessError::None;
    if(!PyArg_ParseTuple(args,"H",&count))
    {
        return NULL;
    }

    if (self->GetInfosRequires[2])
    {
        DAE = _GetRecordInfos(self);
        self->GetInfosRequires[2]= false;
    }

    if (DAE != DataAccessError::None)
    {
        PyErr_SetString(PyExc_RuntimeError,"Can not get recordInfos !");
        return NULL;
    }

    PyObject *tasksTuple = NULL;

    DAE = self->p_ISubscriptionService->ReadRecords(self->subscription_id,count,ISubscriptionService::ReadRecordsRecordsDelegate::create([&](IRscReadEnumerator<RscVariant<512>>& ReadEnumerator){
        uint tasksCount = ReadEnumerator.BeginRead();
        RscVariant<512> currentTask;
        RscVariant<512> currentCycle;
        RscVariant<512> currentData;
        int64_t timestamp;


        std::list<std::list<VariableInfo>>::const_iterator iter_taskInfo = self->RecordInfos->begin();

        tasksTuple = PyTuple_New(tasksCount);
        for(uint task_index=0;task_index<tasksCount;task_index++,iter_taskInfo++)
        {
            ReadEnumerator.ReadNext(currentTask);
            switch (currentTask.GetType())
            {
            case RscType::Array:
            {
                RscArrayReader currentTaskRecordReader{currentTask};  
                
                size_t currentTaskRecordsCounts = currentTaskRecordReader.GetSize();
                PyObject *currentTaskRecordsTuple = PyTuple_New(currentTaskRecordsCounts);
                for (uint TaskRecord_index=0;TaskRecord_index<currentTaskRecordsCounts;TaskRecord_index++)
                {
                    currentTaskRecordReader.ReadNext(currentCycle);
                    switch (currentCycle.GetType())
                    {
                    case RscType::Array:
                        {
                            RscArrayReader currentCycleReader{currentCycle};
                            std::list<VariableInfo>::const_iterator iter_info = iter_taskInfo->begin();

                            PyObject * currentCycleDict = PyDict_New();

                            for (uint data_index=0;data_index<currentCycleReader.GetSize();data_index++,iter_info++)
                            {
                                currentCycleReader.ReadNext(currentData);
                                if(strcmp(iter_info->Name.CStr(),"timestamp")==0)
                                {
                                    if (currentData.GetType()==RscType::Int64)
                                        currentData.CopyTo(timestamp);
                                    else
                                        timestamp = 0;
                                }
                                else
                                {
                                    PyObject* currentValueTuple = PyTuple_New(2);
                                    PyTuple_SetItem(currentValueTuple,0,PythonArp::PyDataAccessService::AutoTypeReadHandler(currentData));
                                    PyTuple_SetItem(currentValueTuple,1,PyLong_FromLongLong(timestamp));
                                    PyDict_SetItemString(currentCycleDict,iter_info->Name.CStr(),currentValueTuple);
                                    Py_XDECREF(currentValueTuple);
                                }
                            }
                            PyTuple_SetItem(currentTaskRecordsTuple,TaskRecord_index,currentCycleDict);
                        }
                        break;
                    default:
                        Log::Error("Unhanded cycle Type :{}",currentCycle.GetType());

                        Py_INCREF(Py_None);
                        PyTuple_SetItem(currentTaskRecordsTuple,TaskRecord_index,Py_None);
                        break;
                    }
                }

                PyTuple_SetItem(tasksTuple,task_index,currentTaskRecordsTuple);
                break;
            }
            default:
            {
                Log::Error("Unhanded task Type :{}",currentTask.GetType());

                Py_INCREF(Py_None);
                PyTuple_SetItem(tasksTuple,task_index,Py_None);
                break;
            }
            }
        }
        ReadEnumerator.EndRead();
    }));

    if (tasksTuple == NULL)
    {
        Py_INCREF(Py_None);
        tasksTuple = Py_None;
    }

    return Py_BuildValue("NN",PyUnicode_FromString(Enum<DataAccessError>(DAE).ToString().CStr()),tasksTuple);
}





/* -------------------------------------------------------------------------- */
/*                             Subcription_methods                            */
/* -------------------------------------------------------------------------- */
static PyMethodDef Subcription_methods[] = {
    _SUBSCRIPTION_CREATESUBSCRIPTION_METHODDEF
    _SUBSCRIPTION_RECREATESUBSCRIPTION_METHODDEF
    _SUBSCRIPTION_GETSUBSCRIPTION_METHODDEF
    _SUBSCRIPTION_SETSUBSCRIPTION_METHODDEF
    _SUBSCRIPTION_ADDVARIABLE_METHODDEF
    _SUBSCRIPTION_REMOVEVARIABLE_METHODDEF
    _SUBSCRIPTION_SUBSCRIBE_METHODDEF
    _SUBSCRIPTION_RESUBSCRIBE_METHODDEF
    _SUBSCRIPTION_UNSUBSCRIBE_METHODDEF
    _SUBSCRIPTION_DELETESUBSCRIPTION_METHODDEF
    _SUBSCRIPTION_READVALUES_METHODDEF
    _SUBSCRIPTION_READTIMESTAMPEDVALUES_METHODDEF
    _SUBSCRIPTION_GETRECORDINFOS_METHODDEF
    _SUBSCRIPTION_READRECORDS_METHODDEF
    {NULL, NULL, 0, NULL}};

/* -------------------------------------------------------------------------- */
/*                              Subcription_Type                              */
/* -------------------------------------------------------------------------- */
static PyTypeObject Subcription_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    Subcription__ClassName,             /* tp_name */
    sizeof(Subscription_obj),           /* tp_basicsize */
    0,                                  /* tp_itemsize */
    (destructor)_Subscription_dealloc,  /* tp_dealloc */
    0,                                  /* tp_print */
    0,                                  /* tp_getattr */
    0,                                  /* tp_setattr */
    0,                                  /* tp_reserved */
    0,                                  /* tp_repr */
    0,                                  /* tp_as_number */
    0,                                  /* tp_as_sequence */
    0,                                  /* tp_as_mapping */
    0,                                  /* tp_hash  */
    0,                                  /* tp_call */
    0,                                  /* tp_str */
    0,                                  /* tp_getattro */
    0,                                  /* tp_setattro */
    0,                                  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    Subcription__doc__,                 /* tp_doc */
    0,                                  /* tp_traverse */
    0,                                  /* tp_clear */
    0,                                  /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    0,                                  /* tp_iter */
    0,                                  /* tp_iternext */
    Subcription_methods,                /* tp_methods */
    0,                                  /* tp_members */
    0,                                  /* tp_getset */
    0,                                  /* tp_base */
    0,                                  /* tp_dict */
    0,                                  /* tp_descr_get */
    0,                                  /* tp_descr_set */
    0,                                  /* tp_dictoffset */
    (initproc)_SubscriptionService___init__,      /* tp_init */
    0,                                  /* tp_alloc */
    PyType_GenericNew,                  /* tp_new */
};

int AddObject(PyObject* builtinsObject)
{
    int ret = -1;
    if(PyType_Ready(&Subcription_Type)<0)
    {
        goto _ERROR;
    }
    else
    {
        Py_INCREF(&Subcription_Type);
        ret = PyModule_AddObject(builtinsObject,Subcription__ClassName,(PyObject*)&Subcription_Type);
        if (ret!=0) goto _ERROR;
        ret = PyModule_AddIntMacro(builtinsObject,SUBSCRIPTION_CLOSEDREALTIME);
        if (ret!=0) goto _ERROR;
        ret = PyModule_AddIntMacro(builtinsObject,SUBSCRIPTION_DIRECTREAD);
        if (ret!=0) goto _ERROR;
        ret = PyModule_AddIntMacro(builtinsObject,SUBSCRIPTION_HIGHPERFORMANCE);
        if (ret!=0) goto _ERROR;
        ret = PyModule_AddIntMacro(builtinsObject,SUBSCRIPTION_REALTIME);
        if (ret!=0) goto _ERROR;
        ret = PyModule_AddIntMacro(builtinsObject,SUBSCRIPTION_RECORDING);
        if (ret!=0) goto _ERROR;
    }
    return ret;
_ERROR:
    Arp::System::Commons::Diagnostics::Logging::Log::Error("Internal Error of 'SubcriptionService Class' type define");
    return ret;
}
}